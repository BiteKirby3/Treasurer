#include "compte.h"

Compte::Compte(int id, double solde, double soldeDernierRapprochement, QDate dernierRapprochement, QString type, QString nom, QDate derniereModification, bool virtuel, int idParent)
{
    this->id = id;
    this->solde = solde;
    this->soldeDernierRapprochement = soldeDernierRapprochement;
    this->dernierRapprochement = dernierRapprochement;
    this->type = type;
    this->nom = nom;
    this->derniereModification = derniereModification;
    this->virtuel = virtuel;
    this->idParent = idParent;
}

QVector<Compte> Compte::getComptes(QString typeCompte)
{
    QVector<Compte> comptes;
    QSqlQuery query;
    query.prepare("SELECT * FROM compte WHERE id_association = :id AND type = :type ORDER BY id_compte_parent NULLS FIRST, nom");
    query.bindValue(":id", CompteController::getInstance()->idAssociation);
    query.bindValue(":type", typeCompte);

    if(query.exec())
    {
        while(query.next())
        {
            int id = query.value(0).toInt();
            double solde = query.value(1).toDouble();
            double soldeDernierRapprochement = query.value(2).toDouble();
            QDate dernierRapprochement = query.value(3).toDate();
            QString type = query.value(4).toString();
            QString nom = query.value(5).toString();
            QDate derniereModification = query.value(7).toDate();
            int idParent = query.value(8).toInt();
            bool virtuel = query.value(9).toBool();

            Compte compte(id, solde, soldeDernierRapprochement, dernierRapprochement, type, nom, derniereModification, virtuel, idParent);
            comptes.push_back(compte);
        }
    }

    return comptes;
}

QVector<Compte> Compte::getComptesVirtuels(QString typeCompte)
{
    QVector<Compte> comptes;

    QSqlQuery query;
    query.prepare("SELECT * FROM compte WHERE id_association = :id AND type = :type AND virtuel = TRUE ORDER BY id_compte_parent NULLS FIRST");
    query.bindValue(":id", CompteController::getInstance()->idAssociation);
    query.bindValue(":type", typeCompte);

    if(query.exec())
    {
        while(query.next())
        {
            int id = query.value(0).toInt();
            double solde = query.value(1).toDouble();
            double soldeDernierRapprochement = query.value(2).toDouble();
            QDate dernierRapprochement = query.value(3).toDate();
            QString type = query.value(4).toString();
            QString nom = query.value(5).toString();
            QDate derniereModification = query.value(7).toDate();
            int idParent = query.value(8).toInt();
            bool virtuel = query.value(9).toBool();

            Compte compte(id, solde, soldeDernierRapprochement, dernierRapprochement, type, nom, derniereModification, virtuel, idParent);
            comptes.push_back(compte);
        }
    }

    return comptes;
}

void Compte::editDerniereModification(int idCompte)
{
    QSqlQuery query;
    query.prepare("UPDATE compte SET derniere_modification = :date WHERE id = :id");
    query.bindValue(":id", idCompte);
    query.bindValue(":date", QDate::currentDate());
    query.exec();
}

int Compte::getId()
{
    return this->id;
}

double Compte::getSolde()
{
    return this->solde;
}

double Compte::getSoldeDernierRapprochement()
{
    return this->soldeDernierRapprochement;
}

QDate Compte::getDernierRapprochement()
{
    return this->dernierRapprochement;
}

QString Compte::getType()
{
    return this->type;
}

QString Compte::getNom()
{
    return this->nom;
}

QDate Compte::getDerniereModification()
{
    return this->derniereModification;
}

bool Compte::isVirtuel()
{
    return this->virtuel;
}

int Compte::getIdParent()
{
    return this->idParent;
}

void Compte::setDerniereModification(QDate date)
{
    this->derniereModification = date;
}
