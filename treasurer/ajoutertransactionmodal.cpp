#include "ajoutertransactionmodal.h"
#include "ui_ajoutertransactionmodal.h"

AjouterTransactionModal::AjouterTransactionModal(QString typeCompte, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterCompteModal)
{
    this->typeCompte = typeCompte;
    ui->setupUi(this);
}

AjouterTransactionModal::~AjouterTransactionModal()
{
    delete ui;
}

void AjouterTransactionModal::on_cancel_button_clicked()
{
    this->close();
}

void AjouterCompteModal::setTitreModal(QString titre)
{
    ui->titreModal->setText(titre);
}

void AjouterCompteModal::setComptesParents()
{
    ui->compteParent->addItem("");

    QVector<Compte> comptes = Compte::getComptesVirtuels(this->typeCompte);

    foreach (Compte compte, comptes)
    {
        ui->compteParent->addItem(compte.getNom(), compte.getId());
    }
}

void AjouterCompteModal::setComptesCapitauxPropres()
{
    QVector<Compte> comptes = Compte::getComptes("passif");

    foreach (Compte compte, comptes)
    {
        ui->comptesCapitauxPropres->addItem(compte.getNom(), compte.getId());
    }
}

void AjouterCompteModal::on_validate_button_clicked()
{
    CompteView* parent = qobject_cast<CompteView*>(this->parent());
    Compte::ajouterCompte(ui->virtuel->isChecked(), parent->getTypeCompte(), ui->nom->text(),  ui->soldeInitial->text().toDouble(), ui->compteParent->currentData().toInt());
    parent->creerArborescence();
    this->close();
}

void AjouterCompteModal::on_virtuel_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        ui->soldeInitial->setDisabled(false);
        ui->comptesCapitauxPropres->setDisabled(false);
    }
    else
    {
        ui->soldeInitial->setDisabled(true);
        ui->comptesCapitauxPropres->setDisabled(true);
    }
}
