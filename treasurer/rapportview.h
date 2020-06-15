#ifndef RAPPORTVIEW_H
#define RAPPORTVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "rapport.h"
#include "rapportsview.h"
#include "connexionview.h"

namespace Ui {
class RapportView;
}

class RapportView: public QMainWindow
{
    //Q_OBJECT
public:
    explicit RapportView(QString typeRapport, QWidget *parent = nullptr);
    ~RapportView();

private slots:
    /*
    void on_logout_button_clicked();
    void on_rapports_button_clicked();
    void on_comptes_button_clicked();
    */

private:
    Ui::RapportView *ui;
    QString typeRapport;
};

#endif // RAPPORTVIEW_H
