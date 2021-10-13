#ifndef EDITERCOMPTEMODAL_H
#define EDITERCOMPTEMODAL_H

#include <QMainWindow>
#include "compteview.h"
#include <QMessageBox>
#include <stdexcept>

namespace Ui {
class EditerCompteModal;
}

class EditerCompteModal : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditerCompteModal(QWidget *parent = nullptr);
    ~EditerCompteModal();
    void setInfo();
    void setComptesParents();

private slots:
    void on_cancel_button_clicked();

    void on_delete_button_clicked();

    void on_validate_button_clicked();

private:
    Ui::EditerCompteModal *ui;
};

#endif // EDITERCOMPTEMODAL_H
