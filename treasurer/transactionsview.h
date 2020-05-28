#ifndef TRANSACTIONSVIEW_H
#define TRANSACTIONSVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <iostream>

#include "connexionview.h"
#include "compteview.h"

namespace Ui {
class TransactionsView;
}

class TransactionsView : public QMainWindow
{
    Q_OBJECT

public:
    explicit TransactionsView(QWidget *parent = nullptr);
    ~TransactionsView();

    /*
    void setSoldeActifsLabel(double solde);
    void setSoldePassifsLabel(double solde);
    void setSoldeRecettesLabel(double solde);
    void setSoldeDepensesLabel(double solde);
    */
private slots:
    void on_logout_button_clicked();
    void on_transactions_button_clicked();
    /*
    void on_detail_actifs_button_clicked();
    void on_detail_passifs_button_clicked();
    void on_detail_depenses_button_clicked();
    void on_detail_recettes_button_clicked();
    */
private:
    Ui::TransactionsView *ui;
};

#endif // TRANSACTIONSVIEW_H
