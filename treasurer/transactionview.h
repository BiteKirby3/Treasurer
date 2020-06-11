#ifndef TRANSACTIONVIEW_H
#define TRANSACTIONVIEW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDebug>

#include "comptecontroller.h"
#include "compte.h"
#include "transaction.h"
#include "connexionview.h"
#include "rapportsview.h"
#include "ajoutercomptemodal.h"
#include "rapprochercomptemodal.h"
#include "cloturemodal.h"
#include "operation.h"

namespace Ui {
class TransactionView;
}

class TransactionView : public QMainWindow
{
    Q_OBJECT

public:
    explicit TransactionView(QWidget *parent = nullptr);
    ~TransactionView();
    void afficherTransactions();

private slots:
    void on_comptes_button_clicked();
    void on_rapports_button_clicked();
    void on_cloture_button_clicked();
    void on_ajouter_transaction_button_clicked();
    void on_logout_button_clicked();

private:
    Ui::TransactionView *ui;
};

#endif // TRANSACTIONVIEW_H
