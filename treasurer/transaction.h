#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDebug>
#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>


class Transaction
{
public:
    Transaction() {};
    Transaction(int id, QDate date, QString reference, QString titre, bool rapproche, double credit, double debit);
    int getId();
    QDate getDate();
    QString getReference();
    QString getTitre();
    bool isRapproche();
    double getCredit();
    double getDebit();
    void setDate(QDate date);
    void setReference(QString reference);
    void setTitre(QString titre);
    void setRapproche(bool rapproche);
    void setCredit(double credit);
    void setDebit(double debit);
    static QVector<Transaction> getTransactionParDate();
    static QVector<Transaction> getTransactionsDuCompte(int idCompte);
    static void editTransactions(QVector<Transaction> transactions, int idCompte);
    static int ajouterTransaction(int idCompte, QString reference, QString titre, double credit, double debit);
    static void ajouterTransaction(int idCompte,int idTransaction, double credit, double debit);
    static void rapprocherCompte(int idCompte);

private:
    int id;
    QDate date;
    QString reference;
    QString titre;
    bool rapproche;
    double credit;
    double debit;
};

Q_DECLARE_METATYPE(Transaction)

#endif // TRANSACTION_H
