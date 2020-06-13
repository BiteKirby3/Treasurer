#include "ajoutertransactionmodal.h"
#include "ui_ajoutertransactionmodal.h"

using namespace std;
#include "iostream"

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
    cout<<this->comptes.count();
}

AjouterTransactionModal::~AjouterTransactionModal()
{
    delete ui;
}

void AjouterTransactionModal::on_ajouter_button_clicked()
{
    QComboBox* compte=new QComboBox();
    QLineEdit* credit=new QLineEdit();
    QLineEdit* debit=new QLineEdit();
    this->comptes.push_back(compte);
    this->credits.push_back(credit);
    this->debits.push_back(debit);

    QVBoxLayout* lcompte=new QVBoxLayout();
    QVBoxLayout* lcredit=new QVBoxLayout();
    QVBoxLayout* ldebit=new QVBoxLayout();
    lcompte->addWidget(compte);
    lcredit->addWidget(credit);
    ldebit->addWidget(debit);
    this->ui->triplets->addLayout(lcompte,this->nbCompteajoute,0);
    this->ui->triplets->addLayout(lcredit,this->nbCompteajoute,1);
    this->ui->triplets->addLayout(ldebit,this->nbCompteajoute,2);
    this->nbCompteajoute++;

    cout<<this->comptes.count();
}

void AjouterTransactionModal::on_cancel_button_clicked()
{
     this->close();
}

void AjouterTransactionModal::on_validate_button_clicked()
{
    TransactionView* tv= qobject_cast<TransactionView*>(this->parent());

    tv->actualiser();
    this->close();
}
