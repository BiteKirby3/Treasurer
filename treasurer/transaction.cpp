#include "transaction.h"

Transaction::Transaction (int id,QDate date,QString reference,QString titre,bool rapproche){
    this->id = id;
    this->date = date;
    this->reference = reference;
    this->titre = titre;
    this->rapproche = rapproche;
}


Transaction::Transaction(int id, QDate date, QString reference, QString titre, bool rapproche, double credit, double debit)
{
    this->id = id;
    this->date = date;
    this->reference = reference;
    this->titre = titre;
    this->rapproche = rapproche;
    this->credit = credit;
    this->debit = debit;
}

int Transaction::getId()
{
    return this->id;
}

QDate Transaction::getDate()
{
    return this->date;
}

QString Transaction::getReference()
{
    return this->reference;
}

QString Transaction::getTitre()
{
    return this->titre;
}

bool Transaction::isRapproche()
{
    return this->rapproche;
}

double Transaction::getCredit()
{
    return this->credit;
}

double Transaction::getDebit()
{
    return this->debit;
}

void Transaction::setDate(QDate date)
{
    this->date = date;
}

void Transaction::setReference(QString reference)
{
    this->reference = reference;
}

void Transaction::setTitre(QString titre)
{
    this->titre = titre;
}

void Transaction::setRapproche(bool rapproche)
{
    this->rapproche = rapproche;
}

void Transaction::setCredit(double credit)
{
    this->credit = credit;
}

void Transaction::setDebit(double debit)
{
    this->debit = debit;
}

QVector<Transaction> Transaction::getTransactionParDate(){
    QVector<Transaction> transactions;
    QVector<int> idComptes;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT t.id,t.date,t.reference,t.titre,t.rapproche \
                   FROM transac t,operation o,compte c\
                   WHERE t.id=o.id_transaction AND o.id_Compte=c.id AND id_association=:id\
                   ORDER BY date");
    query.bindValue(":id", CompteController::getInstance()->idAssociation);
                  if(query.exec())
                  {
                      while(query.next()) {
                          int id = query.value(0).toInt();
                          QDate date = query.value(1).toDate();
                          QString reference = query.value(2).toString();
                          QString titre = query.value(3).toString();
                          bool rapproche = query.value(4).toBool();
                          Transaction transaction(id, date, reference, titre, rapproche);
                          transactions.push_back(transaction);
                      }
                  }
    return transactions;
}

QVector<Transaction> Transaction::getTransactionsDuCompte(int idCompte)
{
    QVector<Transaction> transactions;
    QSqlQuery query;
    query.prepare("SELECT t.id, t.date, t.reference, t.titre, t.rapproche, o.credit, o.debit \
                   FROM transac t, operation o \
                   WHERE o.id_compte = :idCompte \
                   AND o.id_transaction = t.id \
                   ORDER BY t.date");

    query.bindValue(":idCompte", idCompte);

    if(query.exec())
    {
        while(query.next()) {
            int id = query.value(0).toInt();
            QDate date = query.value(1).toDate();
            QString reference = query.value(2).toString();
            QString titre = query.value(3).toString();
            bool rapproche = query.value(4).toBool();
            double credit = query.value(5).toDouble();
            double debit = query.value(6).toDouble();

            Transaction transaction(id, date, reference, titre, rapproche, credit, debit);
            transactions.push_back(transaction);
        }
    }

    return transactions;
}

void Transaction::editTransactions(QVector<Transaction> transactions, int idCompte)
{
    foreach (Transaction transaction, transactions)
    {
        QSqlQuery query1;
        query1.prepare("UPDATE transac \
                       SET reference = :reference, titre = :titre, date = :date \
                       WHERE id = :id");

        query1.bindValue(":id", transaction.getId());
        query1.bindValue(":reference", transaction.getReference());
        query1.bindValue(":titre", transaction.getTitre());
        query1.bindValue(":date", transaction.getDate());
        query1.exec();

        QSqlQuery query2;
        query2.prepare("UPDATE operation \
                       SET debit = :debit, credit = :credit \
                       WHERE id_compte = :idCompte \
                       AND id_transaction = :idTransaction");

        query2.bindValue(":idTransaction", transaction.getId());
        query2.bindValue(":idCompte", idCompte);
        query2.bindValue(":debit", transaction.getDebit());
        query2.bindValue(":credit", transaction.getCredit());
        query2.exec();

    }
}

void Transaction::rapprocherCompte(int idCompte)
{
    QSqlQuery query1;
    query1.prepare("UPDATE transac \
                   SET rapproche = TRUE \
                   WHERE id IN (SELECT id_transaction FROM operation WHERE id_compte = :idCompte);");
    query1.bindValue(":idCompte", idCompte);
    query1.exec();

    QSqlQuery query2;
    query2.prepare("UPDATE compte \
                   SET date_dernier_rapprochement = :date, solde_dernier_rapprochement = solde \
                   WHERE id = :idCompte;");
    query2.bindValue(":idCompte", idCompte);
    query2.bindValue(":date", QDate::currentDate());
    query2.exec();
}

int Transaction::ajouterTransaction(int idCompte, QString reference, QString titre, double credit, double debit)
{
    //Mettre à jour la table transac
    QSqlQuery query1;
    query1.prepare("INSERT INTO transac(date,reference,titre,rapproche)"
                  "VALUES (:date,:reference,:titre,:rapproche)");
    query1.bindValue(":date",QDate::currentDate());
    query1.bindValue(":reference",reference);
    query1.bindValue(":titre",titre);
    query1.bindValue(":rapproche",false);
    query1.exec();
    //Mettre à jour la table Compte
    QSqlQuery query2;
    query2.prepare("SELECT solde,type\
                   FROM compte\
                   WHERE id = :idCompte");
    query2.bindValue(":idCompte", idCompte);
    double solde;
    QString type;
    if(query2.exec())
    {
        while(query2.next()) {
            solde= query2.value(0).toDouble();
            type=query2.value(1).toString();
        }
     }
    double montant=credit-debit;
    if(montant>=0){
        if(type=="actif"||type=="depense")
            solde=solde-montant;
        else
            solde=solde+montant;
    }
    else{
        montant=-montant;
        if(type=="actif"||type=="depense")
            solde=solde+montant;
        else
            solde=solde-montant;
    }
    QSqlQuery query3;
    query3.prepare("UPDATE compte \
                   SET solde = :solde,derniere_modification = :date\
                   WHERE id = :idCompte;");
    query3.bindValue(":idCompte", idCompte);
    query3.bindValue(":solde", solde);
    query3.bindValue(":date",QDate::currentDate());
    query3.exec();
    //Mettre à jour la table opération
    int idTransaction=query1.lastInsertId().toInt();
    QSqlQuery query4;
    query4.prepare("INSERT INTO operation(id_compte, id_transaction, debit, credit)"
                  "VALUES (:idcompte,:idtransaction,:debit,:credit)");
    query4.bindValue(":idcompte", idCompte);
    query4.bindValue(":idtransaction", idTransaction);
    query4.bindValue(":debit",debit);
    query4.bindValue(":credit",credit);
    query4.exec();
    return idTransaction;
}

void Transaction::ajouterTransaction(int idCompte,int idTransaction, double credit, double debit){
    //Mettre à jour la table Compte
    QSqlQuery query1;
    query1.prepare("SELECT solde,type\
                   FROM compte\
                   WHERE id = :idCompte");
    query1.bindValue(":idCompte", idCompte);
    double solde;
    QString type;
    if(query1.exec())
    {
        while(query1.next()) {
            solde= query1.value(0).toDouble();
            type=query1.value(1).toString();
        }
     }
    double montant=credit-debit;
    if(montant>=0){
        if(type=="actif"||type=="depense")
            solde=solde-montant;
        else
            solde=solde+montant;
    }
    else{
        montant=-montant;
        if(type=="actif"||type=="depense")
            solde=solde+montant;
        else
            solde=solde-montant;
    }
    QSqlQuery query2;
    query2.prepare("UPDATE compte \
                   SET solde = :solde,derniere_modification = :date\
                   WHERE id = :idCompte;");
    query2.bindValue(":idCompte", idCompte);
    query2.bindValue(":solde", solde);
    query2.bindValue(":date",QDate::currentDate());
    query2.exec();
    //Mettre à jour la table opération
    QSqlQuery query3;
    query3.prepare("INSERT INTO operation(id_compte, id_transaction, debit, credit)"
                  "VALUES (:idcompte,:idtransaction,:debit,:credit)");
    query3.bindValue(":idcompte", idCompte);
    query3.bindValue(":idtransaction", idTransaction);
    query3.bindValue(":debit",debit);
    query3.bindValue(":credit",credit);
    query3.exec();
}
