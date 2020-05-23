#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>

namespace Ui {
class Connexion;
}

class Connexion : public QMainWindow
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = nullptr);
    ~Connexion();
    void test();

private slots:
    void on_connection_button_clicked();

private:
    Ui::Connexion *ui;
};

#endif // CONNEXION_H
