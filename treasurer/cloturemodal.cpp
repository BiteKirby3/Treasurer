#include "cloturemodal.h"
#include "ui_cloturemodal.h"

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
    if(resultat>0)
        resLabel+=" excédent de "+QString::number(resultat)+"€";
    else
        resLabel+=" déficit de "+QString::number(-resultat)+"€";
    ui->resultatLabel->setText(resLabel);
}
void ClotureModal::on_validate_button_clicked()
{
    //1.transaction répartie permettant de solder les comptes de dépenses

    //2.transaction répartie permettant de solder les comptes de recettes

    //3.Transaction qui constate la nature du résultat (ici un excédent)


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
    /*
    TransactionView*  tv= dynamic_cast<TransactionView*>(this->parent());
    if (cv != nullptr) {
    }
    */
    //cas4:RapportsView
    RapportsView* rsv = dynamic_cast<RapportsView*>(this->parent());
    if (rsv != nullptr) {
        rsv->actualiser();
    }
    //cas5:RapportView
    RapportView* rv = dynamic_cast<RapportView*>(this->parent());
    /*if (rs != nullptr) {
        rsv->actualiser();
    }*/

    this->close();
}

void ClotureModal::on_cancel_button_clicked()
{
    this->close();
}

