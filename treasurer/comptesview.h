#ifndef COMPTESVIEW_H
#define COMPTESVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <iostream>

#include "connexionview.h"

namespace Ui {
class ComptesView;
}

class ComptesView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ComptesView(QWidget *parent = nullptr);
    ~ComptesView();
    void setSoldeActifsLabel(double solde);
    void setSoldePassifsLabel(double solde);
    void setSoldeRecettesLabel(double solde);
    void setSoldeDepensesLabel(double solde);

private slots:
    void on_logout_button_clicked();

private:
    Ui::ComptesView *ui;
};

#endif // COMPTESVIEW_H
