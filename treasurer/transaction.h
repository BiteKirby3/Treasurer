#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>


class Transaction
{
public:
    Transaction(int id, QDate date, QString reference, QString titre, bool rapproche, double credit, double debit);
    int getId();
    QDate getDate();
    QString getReference();
    QString getTitre();
    bool isRapproche();
    double getCredit();
    double getDebit();
    static QVector<Transaction> getTransactionsDuCompte(int idCompte);


private:
    int id;
    QDate date;
    QString reference;
    QString titre;
    bool rapproche;
    double credit;
    double debit;
};

#endif // TRANSACTION_H
