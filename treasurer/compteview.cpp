#include "compteview.h"
#include "ui_compteview.h"

CompteView::CompteView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompteView)
{
    ui->setupUi(this);
}

CompteView::~CompteView()
{
    delete ui;
}

void CompteView::setTypeCompteLabel(QString typeCompte) {
    this->ui->typeCompteLabel->setText(typeCompte);
}

void CompteView::on_comptes_button_clicked()
{
    CompteController* compteController = CompteController::getInstance();
    compteController->showComptes();
    this->close();
}

void CompteView::on_logout_button_clicked()
{
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}
