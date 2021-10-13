#ifndef CLOTUREMODAL_H
#define CLOTUREMODAL_H

#include <QMainWindow>
#include <QDateTime>
#include <QCloseEvent>

#include "comptecontroller.h"
#include "transactionview.h"
#include "rapportview.h"
#include "rapportsview.h"
#include "comptesview.h"
#include "compteview.h"
#include "compte.h"
#include "transaction.h"

namespace Ui {
class ClotureModal;
}

class ClotureModal:public QMainWindow
{
    Q_OBJECT
public:
    explicit ClotureModal(QWidget *parent = nullptr);
    ~ClotureModal();
    void setLabels();

private slots:
    void on_validate_button_clicked();
    void on_cancel_button_clicked();

private:
    Ui::ClotureModal *ui;
    void closeEvent (QCloseEvent *event);
};

#endif // CLOTUREMODAL_H
