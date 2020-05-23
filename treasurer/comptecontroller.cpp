#include "comptecontroller.h"
#include "comptesview.h"


CompteController::CompteController()
{
    this->comptesview = new ComptesView;
}

CompteController* CompteController::getInstance()
{
    if (!controller)
    {
        controller = new CompteController();
    }

    return controller;
}

void CompteController::showComptes()
{
    this->comptesview->show();
}

double CompteController::getSoldeComptes(QString type)
{
    QSqlQuery query;
    query.prepare("SELECT SUM(solde) FROM compte WHERE type = :type AND id_association = :id_association");
    query.bindValue(":type", type);
    query.bindValue(":id_association", this->idAssociation);

    if(query.exec() && query.next())
    {
        return query.value(0).toDouble();
    }
    else {
        return 0;
    }
}

void CompteController::setIdAssociation(int id)
{
    this->idAssociation = id;
}

void CompteController::setSoldes() {
    this->comptesview->setSoldeActifsLabel(getSoldeComptes("actifs"));
    this->comptesview->setSoldePassifsLabel(getSoldeComptes("passifs"));
    this->comptesview->setSoldeDepensesLabel(getSoldeComptes("depenses"));
    this->comptesview->setSoldeRecettesLabel(getSoldeComptes("recettes"));
}

CompteController* CompteController::controller = nullptr;
