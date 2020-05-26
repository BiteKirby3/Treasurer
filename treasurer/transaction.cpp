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

