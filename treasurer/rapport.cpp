#include "rapport.h"

Rapport::Rapport(){}

Rapport::Rapport(QString t){
    this->titre=t;
    int id=CompteController::getInstance()->idAssociation;
    setIdAssociation(id);
}

QString Rapport::getTitre(){return this->titre;}

void Rapport::setTitre(QString titre){this->titre=titre;}

int Rapport::getIdAssociation(){return this->idAssociation;}

void Rapport::setIdAssociation(int id){
    this->idAssociation=id;
}
