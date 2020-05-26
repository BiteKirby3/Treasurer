#include "rapprochercomptemodal.h"
#include "ui_rapprochercomptemodal.h"

RapprocherCompteModal::RapprocherCompteModal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RapprocherCompteModal)
{
    ui->setupUi(this);
}

RapprocherCompteModal::~RapprocherCompteModal()
{
    delete ui;
}

void RapprocherCompteModal::setLabels() {
    CompteView* parent = qobject_cast<CompteView*>(this->parent());
    QString titre = "Rapprocher le compte '" + parent->getCompteActuel().getNom() + "'";
    ui->titreModal->setText(titre);

    QString compteLabel = "Souhaitez-vous rapprocher '" + parent->getCompteActuel().getNom() + "' ?";
    ui->compteLabel->setText(compteLabel);

    if (!parent->getCompteActuel().getDernierRapprochement().toString().isNull()) {
        QString dernierRapprochement = "Le solde au dernier rapprochement du " +
                                       parent->getCompteActuel().getDernierRapprochement().toString("dd/MM/yyyy") +
                                       " était de " + QString::number(parent->getCompteActuel().getSoldeDernierRapprochement()) + "€";
        ui->dernierRapprochementLabel->setText(dernierRapprochement);
    }
    else {
        ui->dernierRapprochementLabel->setText("");
    }
}

void RapprocherCompteModal::on_validate_button_clicked()
{
    CompteView* parent = qobject_cast<CompteView*>(this->parent());
    Transaction::rapprocherCompte(parent->getCompteActuel().getId());
    Compte::editDerniereModification(parent->getCompteActuel().getId());
    parent->creerArborescence();
    parent->rapprocherCompteActuel();
    parent->setTransactions();
    this->close();
}

void RapprocherCompteModal::on_cancel_button_clicked()
{
    this->close();
}

