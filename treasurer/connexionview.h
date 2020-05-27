#ifndef CONNEXION_H
#define CONNEXION_H

#include <iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QMainWindow>

#include "ui_connexionview.h"
#include "databasemanager.h"
#include "comptecontroller.h"



namespace Ui {
class ConnexionView;
}

class ConnexionView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnexionView(QWidget *parent = nullptr);
    ~ConnexionView();

private slots:
    void on_connection_button_clicked();

private:
    Ui::ConnexionView *ui;
};

#endif // CONNEXION_H
