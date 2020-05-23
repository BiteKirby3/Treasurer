#include <QtSql>
#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "connexion.h"
#include "databasemanager.h"

using namespace std;

int main(int countArg, char **listArg) {
    QApplication app(countArg, listArg);

    DatabaseManager* dm = DatabaseManager::getInstance();

    if(dm->login()) {
        Connexion* connexion = new Connexion;
        connexion->show();
    }

    return app.exec();
}
