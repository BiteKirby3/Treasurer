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
    static QString getNom(int idCompte);
    static QVector<Compte> getComptes(QString typeCompte);
    static QVector<Compte> getComptesVirtuels(QString typeCompte);
    static void editDerniereModification(int idCompte);
    static void ajouterCompte(bool virtuel, QString typeCompte, QString nom, double solde, int idCompteParent);
    int getId();
    double getSolde();
    double getSoldeDernierRapprochement();
    QDate getDernierRapprochement();
    QString getType();
    QString getNom();
    QDate getDerniereModification();
    bool isVirtuel();
    int getIdParent();
    void setDerniereModification(QDate date);
    void setDateDernierRapprochement(QDate date);
    void setSoldeDernierRapprochement(double solde);

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
