#ifndef RAPPROCHERCOMPTEMODAL_H
#define RAPPROCHERCOMPTEMODAL_H

#include <QMainWindow>

#include "compteview.h"

namespace Ui {
class RapprocherCompteModal;
}

class RapprocherCompteModal : public QMainWindow
{
    Q_OBJECT

public:
    explicit RapprocherCompteModal(QWidget *parent = nullptr);
    ~RapprocherCompteModal();
    void setLabels();

private slots:
    void on_validate_button_clicked();
    void on_cancel_button_clicked();

private:
    Ui::RapprocherCompteModal *ui;
};


#endif // RAPPROCHERCOMPTEMODAL_H
