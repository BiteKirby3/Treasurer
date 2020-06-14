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

QVector<Operation> Operation::getOperationsDuCompte(int idCompte){
    QVector<Operation> ops;
    QSqlQuery query;
    query.prepare("SELECT o.id,o.id_compte,o.id_transaction,o.credit,o.debit FROM operation o,compte c WHERE c.id=o.id_compte and c.id_association = :ida and o.id_compte=:idc");
    query.bindValue(":ida", CompteController::getInstance()->idAssociation);
    query.bindValue(":idc", idCompte);
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

void Operation::updateOperation(int idTransaction, QString nomCompte,double credit,double debit)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM compte WHERE nom=:nom and id_association=:idAsso");
    query.bindValue(":nom", nomCompte);
    query.bindValue(":idAsso",CompteController::getInstance()->idAssociation);
    int idC=0;
    if(query.exec())
    {
        while(query.next())
        {
            idC= query.value(0).toInt();
        }
    }
    QSqlQuery query1;
    query1.prepare("UPDATE operation \
                   SET debit = :debit,credit=:credit\
                   WHERE id_compte= :id1 and id_transaction= :id2;");
    query1.bindValue(":debit", debit);
    query1.bindValue(":credit",credit);
    query1.bindValue(":id1",idC);
    query1.bindValue(":id2",idTransaction);
    query1.exec();
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

