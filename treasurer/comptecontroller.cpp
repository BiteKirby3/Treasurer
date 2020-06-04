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
    query.prepare("SELECT SUM(solde) FROM compte WHERE type = :type AND id_association = :id");
    query.bindValue(":type", type);
    query.bindValue(":id", this->idAssociation);

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
    this->comptesview->setSoldeActifsLabel(getSoldeComptes("actif"));
    this->comptesview->setSoldePassifsLabel(getSoldeComptes("passif"));
    this->comptesview->setSoldeDepensesLabel(getSoldeComptes("depense"));
    this->comptesview->setSoldeRecettesLabel(getSoldeComptes("recette"));
}

void CompteController::setViewLogout(QString view){
    QSqlQuery query;
    query.prepare(QString("UPDATE association SET view_logout=:vl WHERE id=%1").arg(this->idAssociation));
    query.bindValue(":vl",view);
    query.exec();
}

CompteController* CompteController::controller = nullptr;
