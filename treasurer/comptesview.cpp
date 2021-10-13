#include "comptesview.h"
#include "ui_comptesview.h"

ComptesView::ComptesView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComptesView)
{
    ui->setupUi(this);
    this->setMenuButtonColor();
}

ComptesView::~ComptesView()
{
    delete ui;
}

void ComptesView::setMenuButtonColor(){
    this->ui->comptes_button->setStyleSheet("color:rgb(0,0,255)");
    this->ui->cloture_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->rapports_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->transaction_button->setStyleSheet("color:rgb(255,255,255)");
}

void ComptesView::setSoldeActifsLabel(double solde)
{
    this->ui->actifsLabel->setText(QString("%1€").arg(solde));
}

void ComptesView::setSoldePassifsLabel(double solde)
{
    this->ui->passifsLabel->setText(QString("%1€").arg(solde));
}

void ComptesView::setSoldeRecettesLabel(double solde)
{
    this->ui->recettesLabel->setText(QString("%1€").arg(solde));
}

void ComptesView::setSoldeDepensesLabel(double solde)
{
    this->ui->depensesLabel->setText(QString("%1€").arg(solde));
}

void ComptesView::on_rapports_button_clicked()
{
    RapportsView* rapports=new RapportsView;
    rapports->show();
    this->close();
}

void ComptesView::on_cloture_button_clicked()
{
    this->ui->rapports_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->cloture_button->setStyleSheet("color:rgb(0,0,255)");
    this->ui->comptes_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->transaction_button->setStyleSheet("color:rgb(255,255,255)");
    ClotureModal* clo=new ClotureModal(this);
    clo->show();
}

void ComptesView::on_logout_button_clicked()
{
    CompteController::getInstance()->setViewLogout("comptesview");
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}

void ComptesView::on_detail_actifs_button_clicked()
{
    CompteView* compteView = new CompteView("actif");
    compteView->show();
    compteView->setWindowTitle("Treasurer - Actifs");
    compteView->creerArborescence();
    compteView->setTypeCompteLabel();
    this->close();
}

void ComptesView::on_detail_passifs_button_clicked()
{
    CompteView* compteView = new CompteView("passif");
    compteView->show();
    compteView->setWindowTitle("Treasurer - Passifs");
    compteView->creerArborescence();
    compteView->setTypeCompteLabel();
    this->close();
}

void ComptesView::on_detail_depenses_button_clicked()
{
    CompteView* compteView = new CompteView("depense");
    compteView->show();
    compteView->setWindowTitle("Treasurer - Dépenses");
    compteView->creerArborescence();
    compteView->setTypeCompteLabel();
    this->close();
}

void ComptesView::on_detail_recettes_button_clicked()
{
    CompteView* compteView = new CompteView("recette");
    compteView->show();
    compteView->setWindowTitle("Treasurer - Recettes");
    compteView->creerArborescence();
    compteView->setTypeCompteLabel();
    this->close();
}


void ComptesView::on_transaction_button_clicked()
{
    TransactionView* transaction=new TransactionView;
    transaction->show();
    this->close();
}
