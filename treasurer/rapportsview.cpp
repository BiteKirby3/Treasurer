#include "rapportsview.h"
#include "ui_rapportsview.h"

RapportsView::RapportsView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RapportsView)
{
    ui->setupUi(this);
    this->resize( QSize( 1200, 800 ));
    this->setBilanLabel(CompteController::getInstance()->getSoldeComptes("actif"));
    double depense=CompteController::getInstance()->getSoldeComptes("depense");
    double recette=CompteController::getInstance()->getSoldeComptes("recette");
    if(recette-depense>0) {
        this->ui->beneficeOuPerteLable->setText("Bénéfice:");
        this->setCompteDeResultatLabel(recette-depense);
    }
    else{
        this->ui->beneficeOuPerteLable->setText("Perte:");
        this->setCompteDeResultatLabel(depense-recette);
    }
}
RapportsView::~RapportsView()
{
    delete ui;
}

void RapportsView::on_rapports_button_clicked()
{
    RapportsView* rapports=new RapportsView;
    rapports->show();
    this->close();
}
void RapportsView::on_comptes_button_clicked()
{
    CompteController* compteController = CompteController::getInstance();
    compteController->showComptes();
    this->close();
}

void RapportsView::setBilanLabel(double solde)
{
    this->ui->bilanLabel->setText(QString("%1€").arg(solde));
}

void RapportsView::setCompteDeResultatLabel(double solde)
{
    this->ui->compteDeResultatLabel->setText(QString("%1€").arg(solde));
}

void RapportsView::on_logout_button_clicked()
{
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}

void RapportsView::on_detail_bilan_button_clicked()
{
    RapportView* rapView = new RapportView("Bilan");
    rapView->show();
    rapView->setWindowTitle("Bilan");
    this->close();
}

void RapportsView::on_detail_compteresultat_button_clicked()
{
    RapportView* rapView = new RapportView("Compte de résultat");
    rapView->show();
    rapView->setWindowTitle("Compte de résultat");
    this->close();
}