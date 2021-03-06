#ifndef OPERATION_H
#define OPERATION_H

#include <QDebug>
#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>

#include <comptecontroller.h>

class Operation
{
public:
    Operation(){};
    Operation(int id,int idCompte,int idTransaction,double credit,double debit);
    static QVector<Operation> getOperationsDuCompte(int idCompte);
    static QVector<Operation> getOperationDeTran(int idTransac);
    static void updateOperation(int idTransaction, QString nomCompte,double credit,double debit);
    int getId();
    int getIdCompte();
    int getCredit();
    int getDebit();

private:
    int id;
    int idCompte;
    int idTransaction;
    double credit;
    double debit;
};

Q_DECLARE_METATYPE(Operation)

#endif // OPERATION_H
