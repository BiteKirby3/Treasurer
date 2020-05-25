#include "ajoutercomptemodal.h"
#include "ui_ajoutercomptemodal.h"

AjouterCompteModal::AjouterCompteModal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterCompteModal)
{
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

void AjouterCompteModal::setTitreModal(QString titre) {
    ui->titreModal->setText(titre);
}
