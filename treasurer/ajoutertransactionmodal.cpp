#include "ajoutertransactionmodal.h"
#include "ui_ajoutertransactionmodal.h"

AjouterTransactionModal::AjouterTransactionModal(QString typeCompte, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterTransactionModal)
{
    ui->setupUi(this);
}

AjouterCompteModal::~AjouterCompteModal()
{
    delete ui;
}


void AjouterTransactionModal::on_date_userDateChanged(const QDate &date)
{

}

void AjouterTransactionModal::on_reference_cursorPositionChanged(int arg1, int arg2)
{

}

void AjouterTransactionModal::on_intitule_cursorPositionChanged(int arg1, int arg2)
{

}

void AjouterTransactionModal::on_compte_cursorPositionChanged(int arg1, int arg2)
{

}

void AjouterTransactionModal::on_credit_cursorPositionChanged(int arg1, int arg2)
{

}

void AjouterTransactionModal::on_lineEdit_3_cursorPositionChanged(int arg1, int arg2)
{

}

void AjouterTransactionModal::on_cancel_button_clicked()
{

}

void AjouterTransactionModal::on_validate_button_clicked()
{

}
