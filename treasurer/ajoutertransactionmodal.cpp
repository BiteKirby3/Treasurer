#include "ajoutertransactionmodal.h"
#include "ui_ajoutertransactionmodal.h"

#include <QMessageBox>

AjouterTransactionModal::AjouterTransactionModal(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::AjouterTransactionModal)
{
    this->nbCompteajoute=0;
    ui->setupUi(this);
    this->comptes.push_back(this->ui->compte1);
    this->comptes.push_back(this->ui->compte2);
    this->credits.push_back(this->ui->credit1);
    this->credits.push_back(this->ui->credit2);
    this->debits.push_back(this->ui->debit1);
    this->debits.push_back(this->ui->debit2);
    this->setComptes();
}

AjouterTransactionModal::~AjouterTransactionModal()
{
    delete ui;
}

void AjouterTransactionModal::setCompte1(QString compte1){
    this->ui->compte1->setCurrentText(compte1);
}

void AjouterTransactionModal::on_ajouter_button_clicked()
{
    QComboBox* compte=new QComboBox();
    compte->setMinimumSize(170, 30);
    compte->setStyleSheet("background: #f5f5f5;");
    QLineEdit* credit=new QLineEdit();
    credit->setMinimumSize(0, 30);
    credit->setStyleSheet("background: #f5f5f5;");
    QLineEdit* debit=new QLineEdit();
    debit->setMinimumSize(0, 30);
    debit->setStyleSheet("background: #f5f5f5;");
    this->comptes.push_back(compte);
    this->credits.push_back(credit);
    this->debits.push_back(debit);

    QVBoxLayout* lcompte=new QVBoxLayout();
    lcompte->setContentsMargins(11, 0, 18, 14);
    QVBoxLayout* lcredit=new QVBoxLayout();
    lcredit->setContentsMargins(11, 0, 18, 14);
    QVBoxLayout* ldebit=new QVBoxLayout();
    ldebit->setContentsMargins(11, 0, 18, 14);

    lcompte->addWidget(compte);
    lcredit->addWidget(credit);
    ldebit->addWidget(debit);
    this->ui->triplets->addLayout(lcompte,this->nbCompteajoute,0);
    this->ui->triplets->addLayout(lcredit,this->nbCompteajoute,1);
    this->ui->triplets->addLayout(ldebit,this->nbCompteajoute,2);
    this->nbCompteajoute++;  
    compte->addItem("");
    QVector<Compte> comptes = Compte::getComptesNonVirtuels();
    foreach (Compte c, comptes)
    {
        compte->addItem(c.getNom(), c.getId());
    }
}

void AjouterTransactionModal::setComptes()
{
    ui->compte1->addItem("");
    ui->compte2->addItem("");

    QVector<Compte> comptes = Compte::getComptesNonVirtuels();

    foreach (Compte compte, comptes)
    {
        ui->compte1->addItem(compte.getNom(), compte.getId());
        ui->compte2->addItem(compte.getNom(), compte.getId());
    }
}

bool AjouterTransactionModal::comptesvalide()
{
    int nbComptesValides=0;
    QString compteValide="";
    for(int i=0;i<comptes.count();i++){
        if(comptes.at(i)->currentText()!="" && credits.at(i)->text().toDouble()!=debits.at(i)->text().toDouble() && comptes.at(i)->currentText()!=compteValide)
        {
            compteValide=comptes.at(i)->currentText();
            nbComptesValides++;
        }
    }
    return nbComptesValides>=2;
}

bool AjouterTransactionModal::equilibre()
{
    double sommecredit=0;
    double sommedebit=0;
    foreach(QLineEdit* w1, this->credits){
        sommecredit+=w1->text().toDouble();
    }
    foreach(QLineEdit* w2, this->debits){
        sommedebit+=w2->text().toDouble();
    }
    return sommedebit==sommecredit;
}

void AjouterTransactionModal::on_cancel_button_clicked()
{
     this->close();
}

void AjouterTransactionModal::on_validate_button_clicked()
{
    if(!this->comptesvalide())
    {
        QMessageBox::information(this, "Error", "Au moins deux comptes doivent prendre part à la transaction.");
    }
    else if(!this->equilibre())
    {
        QMessageBox::information(this, "Error", "La somme des débits doit être égale à la somme des crédits.");
    }
    else{
        double montant=this->credits.at(0)->text().toDouble()-this->debits.at(0)->text().toDouble();
        int idTransac;
        if(montant>0){
            idTransac=Transaction::ajouterOperation(comptes.at(0)->currentData().toInt(),ui->reference->text(),ui->intitule->text(),montant,0);
        }
        else{
            idTransac=Transaction::ajouterOperation(comptes.at(0)->currentData().toInt(),ui->reference->text(),ui->intitule->text(),0,-montant);
        }

        for(int i=1;i<comptes.count();i++){
            montant=this->credits.at(i)->text().toDouble()-this->debits.at(i)->text().toDouble();
            if(montant>0){
                Transaction::ajouterOperation(comptes.at(i)->currentData().toInt(),idTransac,montant,0);
            }
            else{
                Transaction::ajouterOperation(comptes.at(i)->currentData().toInt(),idTransac,0,-montant);
            }
        }
        TransactionView* tv= dynamic_cast<TransactionView*>(this->parent());
        if(tv!=nullptr)
        {
            tv->actualiser();
        }
        CompteView* cv= dynamic_cast<CompteView*>(this->parent());
        if(cv!=nullptr)
        {
            Compte::editDerniereModification(cv->getCompteActuel().getId());
            cv->creerArborescence();
            cv->setTransactions();
        }
        this->close();
    }
}
