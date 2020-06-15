#ifndef COMPTE_H
#define COMPTE_H

#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "comptecontroller.h"
#include "operation.h"

class Compte
{
public:
    Compte() {};
    Compte(int id, double solde, double soldeDernierRapprochement, QDate dernierRapprochement, QString type, QString nom, QDate derniereModification, bool virtuel, int idParent);
    static QString getNom(int idCompte);
    static QVector<Compte> getComptes(QString typeCompte);
    static QVector<Compte> getComptesVirtuels(QString typeCompte);
    static QVector<Compte> getComptesNonVirtuels();
    static Compte getCompte(int idCompte);
    static void deleteCompte(int idCompte);
    static void editCompte(int id, QString nom, int idCompteParent, bool virtuel);
    static void editDerniereModification(int idCompte);
    static int ajouterCompte(bool virtuel, QString typeCompte, QString nom, double solde, int idCompteParent);
    double calculerSolde();
    void updateSolde(double solde);
    int getId();
    double getSolde();
    void setSolde(double solde);
    double getSoldeDernierRapprochement();
    QDate getDernierRapprochement();
    QString getType();
    QString getNom();
    QDate getDerniereModification();
    bool isVirtuel();
    int getIdParent();
    void setNom(QString nom);
    void setIdCompteParent(int idCompteParent);
    void setVirtuel(bool virtuel);
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
