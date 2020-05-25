#ifndef COMPTECONTROLLER_H
#define COMPTECONTROLLER_H

#include <iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

class ComptesView;

class CompteController
{
public:
    int idAssociation;
    static CompteController* getInstance();
    void showComptes();
    double getSoldeComptes(QString type);
    void setIdAssociation(int id);
    void setSoldes();

private:
    CompteController();
    ComptesView* comptesview;
    static CompteController* controller;
};

#endif // COMPTECONTROLLER_H
