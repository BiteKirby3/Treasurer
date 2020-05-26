#ifndef COMPTEVIEW_H
#define COMPTEVIEW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDebug>

#include "comptecontroller.h"
#include "compte.h"
#include "transaction.h"
#include "connexionview.h"
#include "ajoutercomptemodal.h"
#include "rapprochercomptemodal.h"

namespace Ui {
class CompteView;
}

class CompteView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CompteView(QString typeCompte, QWidget *parent = nullptr);
    ~CompteView();
    void setTypeCompteLabel();
    void creerArborescence();
    void setTransactions();
    QVector<Transaction> getTransactionsModifiees();
    Compte getCompteActuel();
    QString getTypeCompte();
    void rapprocherCompteActuel();

private slots:
    void on_comptes_button_clicked();
    void on_logout_button_clicked();
    void on_arborescence_clicked(const QModelIndex &index);
    void on_ajouter_compte_button_clicked();
    void onItemChanged(QStandardItem* item);
    void on_save_button_clicked();
    void on_rapprocher_button_clicked();

private:
    Ui::CompteView *ui;
    QString typeCompte;
    Compte compteActuel;
    QSet<int> transactionsModifiees;
};

#endif // COMPTEVIEW_H
