#include "rapportview.h"
#include "ui_rapportview.h"


RapportView::RapportView(QString typeRapport, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RapportView)
{
    this->typeRapport=typeRapport;
    ui->setupUi(this);
}


RapportView::~RapportView()
{
    delete ui;
}

/*
void RapportView::on_comptes_button_clicked()
{
    CompteController* compteController = CompteController::getInstance();
    compteController->showComptes();
    this->close();
}

void RapportView::on_rapports_button_clicked()
{
    RapportsView* rapports=new RapportsView;
    rapports->show();
    this->close();
}


void RapportView::on_logout_button_clicked()
{
CompteController::getInstance()->setViewLogout("rapportview");
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}
*/
