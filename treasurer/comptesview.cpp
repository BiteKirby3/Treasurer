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

void ComptesView::on_detail_actifs_button_clicked()
{
    QString typeCompte = "actifs";
    CompteView* compteView = new CompteView;
    compteView->show();
    compteView->setWindowTitle("Treasurer - Actifs");
    compteView->setTypeCompteLabel(typeCompte.toUpper());
    compteView->creerArborescence(typeCompte);
    compteView->selectPremierCompte(typeCompte);
    this->close();
}

void ComptesView::on_detail_passifs_button_clicked()
{
    QString typeCompte = "passifs";
    CompteView* compteView = new CompteView;
    compteView->show();
    compteView->setWindowTitle("Treasurer - Passifs");
    compteView->setTypeCompteLabel(typeCompte.toUpper());
    compteView->creerArborescence(typeCompte);
    compteView->selectPremierCompte(typeCompte);
    this->close();
}

void ComptesView::on_detail_depenses_button_clicked()
{
    QString typeCompte = "depenses";
    CompteView* compteView = new CompteView;
    compteView->show();
    compteView->setWindowTitle("Treasurer - Dépenses");
    compteView->setTypeCompteLabel(typeCompte.toUpper());
    compteView->creerArborescence(typeCompte);
    compteView->selectPremierCompte(typeCompte);
    this->close();
}

void ComptesView::on_detail_recettes_button_clicked()
{
    QString typeCompte = "recettes";
    CompteView* compteView = new CompteView;
    compteView->show();
    compteView->setWindowTitle("Treasurer - Recettes");
    compteView->setTypeCompteLabel(typeCompte.toUpper());
    compteView->creerArborescence(typeCompte);
    compteView->selectPremierCompte(typeCompte);
    this->close();
}
