#include "editercomptemodal.h"
#include "ui_editercomptemodal.h"

EditerCompteModal::EditerCompteModal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditerCompteModal)
{
    ui->setupUi(this);
}

EditerCompteModal::~EditerCompteModal()
{
    delete ui;
}

void EditerCompteModal::setInfo() {
    CompteView* parent = qobject_cast<CompteView*>(this->parent());

    this->setComptesParents();

    QString titre = "Editer le compte '" + parent->getCompteActuel().getNom() + "'";
    ui->titreModal->setText(titre);
    ui->nom->setText(parent->getCompteActuel().getNom());

    if (parent->getCompteActuel().getIdParent())
    {
        int index = ui->compteParent->findData(parent->getCompteActuel().getIdParent());
        ui->compteParent->setCurrentIndex(index);
    }

    if (parent->getCompteActuel().isVirtuel())
    {
        ui->virtuel->setChecked(true);
    }
}

void EditerCompteModal::setComptesParents()
{
    CompteView* parent = qobject_cast<CompteView*>(this->parent());

    ui->compteParent->addItem("");

    QVector<Compte> comptes = Compte::getComptesVirtuels(parent->getTypeCompte());

    foreach (Compte compte, comptes)
    {
        ui->compteParent->addItem(compte.getNom(), compte.getId());
    }
}

void EditerCompteModal::on_cancel_button_clicked()
{
    this->close();
}

void EditerCompteModal::on_delete_button_clicked()
{
    CompteView* parent = qobject_cast<CompteView*>(this->parent());
    Compte::deleteCompte(parent->getCompteActuel().getId());
    this->close();
}

void EditerCompteModal::on_validate_button_clicked()
{
    CompteView* parent = qobject_cast<CompteView*>(this->parent());
    qDebug() << ui->compteParent->currentData().toInt();
    Compte::editCompte(parent->getCompteActuel().getId(), ui->nom->text(), ui->compteParent->currentData().toInt(), ui->virtuel->isChecked());
    parent->updateCompteInfo(ui->nom->text(), ui->compteParent->currentData().toInt(), ui->virtuel->isChecked());
    parent->afficherCompteInfo();
    parent->creerArborescence();
    this->close();
}
