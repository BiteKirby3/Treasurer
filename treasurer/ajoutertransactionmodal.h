#ifndef AJOUTERTRANSACTIONMODAL_H
#define AJOUTERTRANSACTIONMODAL_H

#include <QMainWindow>
#include "transactionview.h"

#include <QWidget>
#include <QtGui>

namespace Ui {
class AjouterTransactionModal;
}


class AjouterTransactionModal:public QMainWindow
{
    Q_OBJECT
public:
    explicit AjouterTransactionModal(QWidget *parent = nullptr);
    ~AjouterTransactionModal();

private slots:
    void on_ajouter_button_clicked();
    void on_cancel_button_clicked();
    void on_validate_button_clicked();

private:
    int nbCompteajoute;
    QVector<QWidget*> comptes;
    QVector<QWidget*> credits;
    QVector<QWidget*> debits;
    Ui::AjouterTransactionModal *ui;
};

#endif // AJOUTERTRANSACTIONMODAL_H
