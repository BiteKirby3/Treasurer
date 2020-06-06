#ifndef AJOUTERTRANSACTIONMODAL_H
#define AJOUTERTRANSACTIONMODAL_H


#include <QMainWindow>
#include "compteview.h"

namespace Ui {
class AjouterTransactionModal;
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

    void on_date_userDateChanged(const QDate &date);

    void on_reference_cursorPositionChanged(int arg1, int arg2);

    void on_intitule_cursorPositionChanged(int arg1, int arg2);

    void on_compte_cursorPositionChanged(int arg1, int arg2);

    void on_credit_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_3_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::AjouterTransactionModal *ui;
    QString typeCompte;
};


#endif // AJOUTERTRANSACTIONMODAL_H
