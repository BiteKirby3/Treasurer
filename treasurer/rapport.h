#ifndef RAPPORT_H
#define RAPPORT_H

#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "comptecontroller.h"

class Rapport
{
public:

    Rapport();
    Rapport(QString t);
    void compteDeResultats();
    void bilan();
    static void editDerniereModification(int idCompte);
    QString getTitre();
    void setTitre(QString titre); //bilan ou compte de resultat
    int getIdAssociation();
    void setIdAssociation(int id);

private:
    QString titre;
    int idAssociation;
};

#endif // RAPPORT_H
