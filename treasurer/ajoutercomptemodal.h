#ifndef AJOUTERCOMPTEMODAL_H
#define AJOUTERCOMPTEMODAL_H

#include <QMainWindow>
#include "compteview.h"

namespace Ui {
class AjouterCompteModal;
}

class AjouterCompteModal : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjouterCompteModal(QString typeCompte, QWidget *parent = nullptr);
    ~AjouterCompteModal();
    void setTitreModal(QString titre);
    void setComptesParents();
    void setComptesCapitauxPropres();

private slots:
    void on_cancel_button_clicked();
    void on_validate_button_clicked();

private:
    Ui::AjouterCompteModal *ui;
    QString typeCompte;
};

#endif // AJOUTERCOMPTEMODAL_H
