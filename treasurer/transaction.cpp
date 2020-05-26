#include "transaction.h"

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

