#include "ajoutercomptemodal.h"
#include "ui_ajoutercomptemodal.h"

AjouterCompteModal::AjouterCompteModal(QString typeCompte, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterCompteModal)
{
    this->typeCompte = typeCompte;
    ui->setupUi(this);
}

AjouterCompteModal::~AjouterCompteModal()
{
    delete ui;
}

void AjouterCompteModal::on_cancel_button_clicked()
{
    this->close();
}

void AjouterCompteModal::setTitreModal(QString titre)
{
    ui->titreModal->setText(titre);
}

void AjouterCompteModal::setComptesParents()
{
    ui->comptesParents->addItem("");

    QVector<Compte> comptes = Compte::getComptesVirtuels(this->typeCompte);

    foreach (Compte compte, comptes)
    {
        ui->comptesParents->addItem(compte.getNom(), compte.getId());
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
    Compte::ajouterCompte(ui->virtuel->isChecked(), parent->getTypeCompte(), ui->nom->text(),  ui->soldeInitial->text().toDouble(), ui->comptesParents->currentData().toInt());
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
