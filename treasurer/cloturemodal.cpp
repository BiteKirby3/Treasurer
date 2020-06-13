#include "cloturemodal.h"
#include "ui_cloturemodal.h"
#include"iostream"
using namespace std;

ClotureModal::ClotureModal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClotureModal)
{
    ui->setupUi(this);
    this->setLabels();
}

ClotureModal::~ClotureModal()
{
    delete ui;
}

void ClotureModal::setLabels() {
    QString resLabel = "Le résultat du "+QDate::currentDate().toString("dd/MM/yyyy")+" est d'un";
    double depense=CompteController::getInstance()->getSoldeComptes("depense");
    double recette=CompteController::getInstance()->getSoldeComptes("recette");
    double resultat=recette-depense;
    if(resultat>0){
        this->ui->validate_button->setVisible(true);
        resLabel+=" excédent de "+QString::number(resultat)+"€";
    }
    else{
        this->ui->validate_button->setVisible(true);
        resLabel+=" déficit de "+QString::number(-resultat)+"€";
    }
    if(resultat==0){
        this->ui->validate_button->setVisible(false);
    }
    ui->resultatLabel->setText(resLabel);
}
void ClotureModal::on_validate_button_clicked()
{
    QVector<Compte> comptespassif=Compte::getComptes("passif");
    bool trouve=false;
    int cpt=0;
    int idResultat;
    while(!trouve && cpt<comptespassif.count()){
        if (comptespassif[cpt].getNom()=="resultat"){
            trouve=true;
            idResultat=comptespassif[cpt].getId();
        }
        cpt++;
    }
    if(!trouve){
        QSqlQuery query;
        query.prepare("INSERT INTO compte (solde, type, nom, id_association, derniere_modification, virtuel) "
                      "VALUES (:solde, :type, :nom, :idAssociation, :derniereModification,:virtuel)");
        query.bindValue(":solde",0);
        query.bindValue(":type", "passif");
        query.bindValue(":nom", "resultat");
        query.bindValue(":idAssociation", CompteController::getInstance()->idAssociation);
        query.bindValue(":derniereModification", QDate::currentDate());
        query.bindValue(":virtuel",false);
        query.exec();
        idResultat=query.lastInsertId().toInt();

    }
    //1.transaction répartie permettant de solder les comptes de dépenses
    double soldedepense=CompteController::getInstance()->getSoldeComptes("depense");
    int idTransaction=Transaction::ajouterTransaction(idResultat,"cloDepense","CLOTURE-DEPENSE",0,soldedepense);
    QVector<Compte> comptsdep=Compte::getComptes("depense");
    foreach(Compte compte, comptsdep){
        if (!compte.isVirtuel() && compte.getSolde()!=0){
            Transaction::ajouterTransaction(compte.getId(),idTransaction,compte.getSolde(),0);
        }
    }
    //2.transaction répartie permettant de solder les comptes de recettes
    double solderecette=CompteController::getInstance()->getSoldeComptes("recette");
    idTransaction=Transaction::ajouterTransaction(idResultat,"cloRecette","CLOTURE-RECETTE",solderecette,0);
    QVector<Compte> comptsrec=Compte::getComptes("recette");
    foreach(Compte compte, comptsrec){
        if (!compte.isVirtuel() && compte.getSolde()!=0){
            Transaction::ajouterTransaction(compte.getId(),idTransaction,0,compte.getSolde());
        }
    }
    //3.Transaction qui constate la nature du résultat
    int idCompteATransferer;
    trouve=false;
    cpt=0;
    if(solderecette-soldedepense>=0){
        while(!trouve && cpt<comptespassif.count()){
            if (comptespassif[cpt].getNom()=="excedent"){
                trouve=true;
                idCompteATransferer=comptespassif[cpt].getId();
            }
            cpt++;
        }
        if(!trouve){
            QSqlQuery query1;
            query1.prepare("INSERT INTO compte (solde, type, nom, id_association, derniere_modification, virtuel) "
                          "VALUES (:solde, :type, :nom, :idAssociation, :derniereModification, :virtuel)");
            query1.bindValue(":solde",0);
            query1.bindValue(":type", "passif");
            query1.bindValue(":nom", "excedent");
            query1.bindValue(":idAssociation", CompteController::getInstance()->idAssociation);
            query1.bindValue(":derniereModification", QDate::currentDate());
            query1.bindValue(":virtuel",false);
            query1.exec();
            idCompteATransferer=query1.lastInsertId().toInt();
        }
    }
    else{
        while(!trouve && cpt<comptespassif.count()){
            if (comptespassif[cpt].getNom()=="deficit"){
                trouve=true;
                idCompteATransferer=comptespassif[cpt].getId();
            }
            cpt++;
        }
        if(!trouve){
            QSqlQuery query2;
            query2.prepare("INSERT INTO compte (solde, type, nom, id_association, derniere_modification, virtuel) "
                          "VALUES (:solde, :type, :nom, :idAssociation, :derniereModification, :virtuel)");
            query2.bindValue(":solde",0);
            query2.bindValue(":type", "passif");
            query2.bindValue(":nom", "excedent");
            query2.bindValue(":idAssociation", CompteController::getInstance()->idAssociation);
            query2.bindValue(":derniereModification", QDate::currentDate());
            query2.bindValue(":virtuel",false);
            query2.exec();
            idCompteATransferer=query2.lastInsertId().toInt();
        }
    }
    idTransaction=Transaction::ajouterTransaction(idResultat,"CONS","Constatation 2019",0,solderecette-soldedepense);
    Transaction::ajouterTransaction(idCompteATransferer,idTransaction,solderecette-soldedepense,0);

    //actualiser le window parent
    //cas1:ComptesView
    ComptesView* csv = dynamic_cast<ComptesView*>(this->parent());
    if (csv != nullptr) {
        CompteController::getInstance()->setSoldes();
    }
    //cas2:CompteView
    CompteView* cv = dynamic_cast<CompteView*>(this->parent());
    if (cv != nullptr) {
        Transaction::rapprocherCompte(cv->getCompteActuel().getId());
        Compte::editDerniereModification(cv->getCompteActuel().getId());
        cv->creerArborescence();
        cv->rapprocherCompteActuel();
        cv->setTransactions();
    }
    //cas3:TransactionView
    TransactionView*  tv= dynamic_cast<TransactionView*>(this->parent());
    if (tv != nullptr) {
        tv->actualiser();
    }

    //cas4:RapportsView
    RapportsView* rsv = dynamic_cast<RapportsView*>(this->parent());
    if (rsv != nullptr) {
        rsv->actualiser();
    }
    //cas5:RapportView
    /*
    RapportView* rv = dynamic_cast<RapportView*>(this->parent());
    if (rs != nullptr) {
        rsv->actualiser();
    }
    */

    this->close();
}

void ClotureModal::on_cancel_button_clicked()
{
    ComptesView* parent = dynamic_cast<ComptesView*>(this->parent());
    if (parent != nullptr) {
       parent->setMenuButtonColor();
    }
    //cas2:CompteView
    CompteView* cv = dynamic_cast<CompteView*>(this->parent());
    if (cv != nullptr) {
        cv->setMenuButtonColor();
    }
    //cas3:TransactionView
    TransactionView*  tv= dynamic_cast<TransactionView*>(this->parent());
    if (tv != nullptr) {
        tv->setMenuButtonColor();
    }

    //cas4:RapportsView
    RapportsView* rsv = dynamic_cast<RapportsView*>(this->parent());
    if (rsv != nullptr) {
        rsv->setMenuButtonColor();
    }
    //cas5:RapportView
    /*
    RapportView* rv = dynamic_cast<RapportView*>(this->parent());
    if (rs != nullptr) {
        rsv->actualiser();
    }
    */
    this->close();
}

