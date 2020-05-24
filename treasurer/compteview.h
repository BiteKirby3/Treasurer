#ifndef COMPTEVIEW_H
#define COMPTEVIEW_H

#include <QMainWindow>

#include "comptecontroller.h"
#include "connexionview.h"

namespace Ui {
class CompteView;
}

class CompteView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CompteView(QWidget *parent = nullptr);
    ~CompteView();
    void setTypeCompteLabel(QString typeCompte);

private slots:
    void on_comptes_button_clicked();

    void on_logout_button_clicked();

private:
    Ui::CompteView *ui;
    QString typeCompte;
};

#endif // COMPTEVIEW_H
