#ifndef RAPPORTVIEW_H
#define RAPPORTVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>
#include <QStandardItemModel>

#include "rapportsview.h"
#include "connexionview.h"
#include "compte.h"

namespace Ui {
class RapportView;
}

class RapportView: public QMainWindow
{
    Q_OBJECT
public:
    explicit RapportView(QString typeRapport, QWidget *parent = nullptr);
    ~RapportView();
    void setTypeRapportLabel(QString typeRapport);
    void setDateLabel(QString date);
    void setRapport();
    QMap<int, QVector<QString>> creerArborescence(QString typeCompte, double* soldeTotal);
    QMap<int, double*> calculSoldes(int id, QMap<int, QVector<int>> successors, QMap<int, double*> soldesComptes);
    QMap<int, QVector<QString>> ordreArborescence(QMap<int, QVector<QString>> result,
                                                  int idRacine,
                                                  QMap<int, QVector<int>> successors,
                                                  QMap<int, QString> nomsComptes,
                                                  QMap<int, QString> soldesComptes,
                                                  int count);

private slots:
    void on_logout_button_clicked();
    void on_rapports_button_clicked();
    void on_comptes_button_clicked();
    void on_transaction_button_clicked();

private:
    Ui::RapportView *ui;
    QString typeRapport;
    int idRacine = -1;
};

#endif // RAPPORTVIEW_H
