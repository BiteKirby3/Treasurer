#ifndef AJOUTERCOMPTEMODAL_H
#define AJOUTERCOMPTEMODAL_H

#include <QMainWindow>

namespace Ui {
class AjouterCompteModal;
}

class AjouterCompteModal : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjouterCompteModal(QWidget *parent = nullptr);
    ~AjouterCompteModal();
    void setTitreModal(QString titre);

private slots:
    void on_cancel_button_clicked();

private:
    Ui::AjouterCompteModal *ui;
};

#endif // AJOUTERCOMPTEMODAL_H
