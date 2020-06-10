#include "transactionview.h"
#include "ui_transactionview.h"

TransactionView::TransactionView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TransactionView)
{
    ui->setupUi(this);
    this->ui->rapports_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->cloture_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->comptes_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->transaction_button->setStyleSheet("color:rgb(0,0,255)");
}

TransactionView::~TransactionView()
{
    delete ui;
}

void TransactionView::on_comptes_button_clicked()
{
    CompteController* compteController = CompteController::getInstance();
    compteController->showComptes();
    this->close();
}

void TransactionView::on_rapports_button_clicked()
{
    RapportsView* rapports=new RapportsView;
    rapports->show();
    this->close();
}


void TransactionView::on_logout_button_clicked()
{
    CompteController::getInstance()->setViewLogout("transactionview");
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}



void TransactionView::on_ajouter_transaction_button_clicked()
{

}

void TransactionView::on_cloture_button_clicked()
{
    this->ui->rapports_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->cloture_button->setStyleSheet("color:rgb(0,0,255)");
    this->ui->comptes_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->transaction_button->setStyleSheet("color:rgb(255,255,255)");
    ClotureModal* clo=new ClotureModal;
    clo->show();
}

