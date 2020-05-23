#include "connexionview.h"

ConnexionView::ConnexionView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnexionView)
{
    ui->setupUi(this);
    ui->connection_error->setVisible(false);
}

ConnexionView::~ConnexionView()
{
    delete ui;
}

void ConnexionView::on_connection_button_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT id FROM association WHERE identifiant = :login AND mot_de_passe = :password");
    query.bindValue(":login", ui->login->text());
    query.bindValue(":password", ui->password->text());

    if(query.exec() && query.next())
    {
        int id = query.value(0).toInt();

        CompteController* compteController = CompteController::getInstance();
        compteController->setIdAssociation(id);
        compteController->showComptes();
        compteController->setSoldes();

        ui->connection_error->setVisible(false);
        this->close();
    }
    else {
        ui->connection_error->setVisible(true);
    }
}
