#ifndef AJOUTERTRANSACTIONMODAL_H
#define AJOUTERTRANSACTIONMODAL_H


#include <QMainWindow>
#include "compteview.h"

namespace Ui {
class AjouterCompteModal;
}

class AjouterTransactionModal : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjouterTransactionModal(QString typeCompte, QWidget *parent = nullptr);
    ~AjouterTransactionModal();
    void setTitreModal(QString titre);
    void setComptesParents();
    void setComptesCapitauxPropres();

private slots:
    void on_cancel_button_clicked();
    void on_validate_button_clicked();

private:
    Ui::AjouterTransactionModal *ui;
    QString typeCompte;
};


#endif // AJOUTERTRANSACTIONMODAL_H
