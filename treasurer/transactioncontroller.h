#ifndef TRANSACTIONCONTROLLER_H
#define TRANSACTIONCONTROLLER_H


#include <iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

class TransactionsView;

class TransactionController
{
public:
    int idAssociation;
    static TransactionController* getInstance();
    void getTransactions(QString type);
    void setIdAssociation(int id);

private:
    TransactionController();
    TransactionsView* transactionsview;
    static TransactionController* controller;
};
#endif // TRANSACTIONCONTROLLER_H
