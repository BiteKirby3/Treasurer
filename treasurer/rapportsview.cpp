#include "rapportsview.h"
#include "ui_rapportsview.h"

RapportsView::RapportsView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RapportsView)
{
    ui->setupUi(this);
    this->resize( QSize( 1200, 800 ));
    this->ui->rapports_button->setStyleSheet("color:rgb(0,0,255)");
    this->ui->cloture_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->comptes_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->transaction_button->setStyleSheet("color:rgb(255,255,255)");
    this->actualiser();
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

void RapportsView::actualiser()
{
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

void RapportsView::on_logout_button_clicked()
{
    CompteController::getInstance()->setViewLogout("rapportsview");
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}

void RapportsView::on_detail_bilan_button_clicked()
{   
    RapportView* rapView = new RapportView("Bilan");
    rapView->show();
    rapView->setWindowTitle("Bilan");
}

void RapportsView::on_detail_compteresultat_button_clicked()
{
    RapportView* rapView = new RapportView("compte de resultat");
    rapView->show();
    rapView->setWindowTitle("Compte de résultat");
}

void RapportsView::on_cloture_button_clicked()
{
    ClotureModal* clo=new ClotureModal;
    clo->show();
}
