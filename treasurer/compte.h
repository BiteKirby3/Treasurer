#ifndef COMPTE_H
#define COMPTE_H

#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "comptecontroller.h"

class Compte
{
public:
    Compte() {};
    Compte(int id, double solde, double soldeDernierRapprochement, QDate dernierRapprochement, QString type, QString nom, QDate derniereModification, bool virtuel, int idParent);
    static QVector<Compte> getComptes(QString typeCompte);
    static Compte getPremierCompte(QString typeCompte);
    int getId();
    double getSolde();
    double getSoldeDernierRapprochement();
    QDate getDernierRapprochement();
    QString getType();
    QString getNom();
    QDate getDerniereModification();
    bool isVirtuel();
    int getIdParent();

private:
    int id;
    double solde;
    double soldeDernierRapprochement;
    QDate dernierRapprochement;
    QString type;
    QString nom;
    QDate derniereModification;
    bool virtuel;
    int idParent;
};

Q_DECLARE_METATYPE(Compte)

#endif // COMPTE_H