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

QVector<Compte> Compte::getComptesNonVirtuels()
{
    QVector<Compte> comptes;

    QSqlQuery query;
    query.prepare("SELECT * FROM compte WHERE id_association = :id AND virtuel = FALSE ORDER BY id_compte_parent NULLS FIRST");
    query.bindValue(":id", CompteController::getInstance()->idAssociation);

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

Compte Compte::getCompte(int idCompte)
{
    Compte compte;
    QSqlQuery query;
    query.prepare("SELECT * FROM compte WHERE id_association = :idAssociation AND id = :idCompte");
    query.bindValue(":idAssociation", CompteController::getInstance()->idAssociation);
    query.bindValue(":idCompte", idCompte);

    if(query.exec() && query.next())
    {
        int id = query.value(0).toInt();
        double solde = query.value(1).toDouble();
        double soldeDernierRapprochement = query.value(2).toDouble();
        QDate dernierRapprochement = query.value(3).toDate();
        QString type = query.value(4).toString();
        QString nom = query.value(5).toString();
        QDate derniereModification = query.value(7).toDate();
        int idParent = query.value(8).toInt();
        qDebug() << idParent;
        bool virtuel = query.value(9).toBool();

        Compte compte(id, solde, soldeDernierRapprochement, dernierRapprochement, type, nom, derniereModification, virtuel, idParent);
    }

    return compte;
}

void Compte::deleteCompte(int idCompte)
{
    QSqlQuery query;
    query.prepare("DELETE FROM compte WHERE id = :idCompte");
    query.bindValue(":idCompte", idCompte);
    if (!query.exec()) {
        throw std::runtime_error("Ce compte ne peut pas être supprimé");
    }

}
void Compte::editCompte(int id, QString nom, int idCompteParent, bool virtuel)
{
    QSqlQuery query;
    if (idCompteParent != 0)
    {
        query.prepare("UPDATE compte SET nom = :nom, id_compte_parent = :idCompteParent, virtuel = :virtuel, derniere_modification = :date WHERE id = :id;");
        query.bindValue(":idCompteParent", idCompteParent);
    }
    else {
         query.prepare("UPDATE compte SET nom = :nom, virtuel = :virtuel, id_compte_parent = NULL, derniere_modification = :date WHERE id = :id;");
    }

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":virtuel", virtuel);

    query.bindValue(":date", QDate::currentDate());
    query.exec();
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
int Compte::ajouterCompte(bool virtuel, QString typeCompte, QString nom, double solde, int idCompteParent)
{
    QSqlQuery query;
    query.prepare("INSERT INTO compte (solde, type, nom, id_association, derniere_modification, id_compte_parent, virtuel) "
                  "VALUES (:solde, :type, :nom, :idAssociation, :derniereModification, :idCompteParent, :virtuel)");

    if (virtuel)
    {
         query.bindValue(":solde", solde);
    }
    else
    {
         query.bindValue(":solde", QVariant(QVariant::String));
    }

    query.bindValue(":type", typeCompte);
    query.bindValue(":nom", nom);
    query.bindValue(":idAssociation", CompteController::getInstance()->idAssociation);
    query.bindValue(":derniereModification", QDate::currentDate());

    if (idCompteParent == 0)
    {
        query.bindValue(":idCompteParent", QVariant(QVariant::String));
    }
    else {
        query.bindValue(":idCompteParent", idCompteParent);
    }

    query.bindValue(":virtuel", virtuel);
    query.exec();
    int idCompteCree=query.lastInsertId().toInt();

    return idCompteCree;
}

void Compte::setDateDernierRapprochement(QDate date)
{
    this->dernierRapprochement = date;
}

void Compte::setSoldeDernierRapprochement(double solde)
{
    this->soldeDernierRapprochement = solde;
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

void Compte::setSolde(double solde)
{
    this->solde=solde;
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

QString Compte::getNom(int idCompte) {
    QSqlQuery query;
    query.prepare("SELECT nom FROM compte WHERE id=:id");
    query.bindValue(":id", idCompte);
    QString nomCompte;
    if(query.exec())
    {
        while(query.next())
        {
            nomCompte= query.value(0).toString();
        }
    }
    return nomCompte;
}

void Compte::updateSolde(double solde)
{
    QSqlQuery query;
    query.prepare("UPDATE compte \
                   SET solde= :solde\
                   WHERE id= :id");
    query.bindValue(":solde",solde);
    query.bindValue(":id",this->getId());
    query.exec();
}

double Compte::calculerSolde()
{
    double s=0;
    QVector<Operation> ops=Operation::getOperationsDuCompte(this->getId());
    foreach(Operation op,ops)
    {
        if(this->getType()=="actif" || this->getType()=="depense")
        {
            s=s-op.getCredit();
            s=s+op.getDebit();
        }
        else
        {
            s=s+op.getCredit();
            s=s-op.getDebit();
        }
    }
    this->setSolde(s);
    return s;
}

void Compte::setNom(QString nom)
{
    this->nom = nom;
}

void Compte::setIdCompteParent(int idCompteParent)
{
    this->idParent = idCompteParent;
}

void Compte::setVirtuel(bool virtuel)
{
    this->virtuel = virtuel;
}
