#include "operation.h"
using namespace std;
#include "iostream"

Operation::Operation(int id,int idCompte,int idTransaction,double credit=0,double debit=0){
    this->id=id;
    this->idCompte=idCompte;
    this->idTransaction=idTransaction;
    this->credit=credit;
    this->debit=debit;
}

QVector<Operation> Operation::getOperations(){
    QVector<Operation> ops;
    QSqlQuery query;
    query.prepare("SELECT o.id,o.id_compte,o.id_transaction,o.credit,o.debit FROM operation o,transac t,compte c WHERE t.id=o.id_transaction AND c.id=o.id_compte and c.id_association = :id ORDER BY t.date");
    query.bindValue(":id", CompteController::getInstance()->idAssociation);
    if(query.exec())
    {
        while(query.next())
        {
            int idOp= query.value(0).toInt();
            int idCom = query.value(1).toInt();
            int idTransac = query.value(2).toInt();
            double cre= query.value(3).toDouble();
            double deb= query.value(4).toDouble();
            Operation op(idOp, idCom,idTransac,cre,deb);
            ops.push_back(op);
        }
    }
    else{
        qDebug() << "error:" << query.lastError().text();
    }
    return ops;
}

QVector<Operation> Operation::getOperationDeTran(int idTransac){
    QVector<Operation> ops;
    QSqlQuery query;
    query.prepare("SELECT id,id_compte,id_transaction,credit,debit FROM operation WHERE id_transaction=:id");
    query.bindValue(":id",idTransac);
    if(query.exec())
    {
        while(query.next())
        {
            int idOp= query.value(0).toInt();
            int idCom = query.value(1).toInt();
            int idTransac = query.value(2).toInt();
            double cre= query.value(3).toDouble();
            double deb= query.value(4).toDouble();
            Operation op(idOp, idCom,idTransac,cre,deb);
            ops.push_back(op);
        }
    }
    return ops;
}

int Operation::getId(){
    return this->id;
}

int Operation::getIdCompte()
{
    return this->idCompte;
}

int Operation::getCredit()
{
    return this->credit;
}

int Operation::getDebit()
{
    return this->debit;
}

