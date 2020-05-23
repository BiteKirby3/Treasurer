#include "comptesview.h"
#include "ui_comptesview.h"

ComptesView::ComptesView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComptesView)
{
    ui->setupUi(this);
}

ComptesView::~ComptesView()
{
    delete ui;
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

void ComptesView::on_logout_button_clicked()
{
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}
