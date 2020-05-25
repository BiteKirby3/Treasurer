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
    QSqlQuery query;
    query.prepare("INSERT INTO compte (solde, type, nom, id_association, derniere_modification, id_compte_parent, virtuel) "
                  "VALUES (:solde, :type, :nom, :idAssociation, :derniereModification, :idCompteParent, :virtuel)");
    query.bindValue(":solde", ui->soldeInitial->text().toDouble());
    query.bindValue(":type", this->typeCompte);
    query.bindValue(":nom", ui->nom->text());
    query.bindValue(":idAssociation", CompteController::getInstance()->idAssociation);
    query.bindValue(":derniereModification", QDate::currentDate());

    if (ui->comptesParents->currentData().toInt() == 0)
    {
        query.bindValue(":idCompteParent", QVariant(QVariant::String));
    }
    else {
        query.bindValue(":idCompteParent", ui->comptesParents->currentData().toInt());
    }

    query.bindValue(":virtuel", ui->virtuel->isChecked());

    if(query.exec())
    {
        CompteView* parent = qobject_cast<CompteView*>(this->parent());
        parent->creerArborescence();
        this->close();
    }
}
