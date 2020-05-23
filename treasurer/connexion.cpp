#include <iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

#include "connexion.h"
#include "ui_connexion.h"
#include "databasemanager.h"

Connexion::Connexion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    ui->connection_error->setVisible(false);
}

Connexion::~Connexion()
{
    delete ui;
}

void Connexion::on_connection_button_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT id FROM association WHERE identifiant = :login AND mot_de_passe = :password");
    query.bindValue(":login", ui->login->text());
    query.bindValue(":password", ui->password->text());

    if(query.exec() && query.next())
    {
        int id = query.value(0).toInt();
        ui->connection_error->setVisible(false);
    }
    else {
        ui->connection_error->setVisible(true);
    }
}
