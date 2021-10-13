#ifndef RAPPORTSVIEW_H
#define RAPPORTSVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "cloturemodal.h"
#include "rapportview.h"
#include "connexionview.h"

namespace Ui {
class RapportsView;
}

class RapportsView: public QMainWindow
{
    Q_OBJECT
public:
    explicit RapportsView(QWidget *parent = nullptr);
    ~RapportsView();
    void setBilanLabel(double solde);
    void setCompteDeResultatLabel(double solde);
    void actualiser();
    void setMenuButtonColor();
private slots:
    void on_cloture_button_clicked();
    void on_logout_button_clicked();
    void on_transaction_button_clicked();
    void on_rapports_button_clicked();
    void on_comptes_button_clicked();
    void on_detail_bilan_button_clicked();
    void on_detail_compteresultat_button_clicked();

private:
    Ui::RapportsView *ui;
};

#endif // RAPPORTSVIEW_H
