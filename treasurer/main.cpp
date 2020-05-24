#include <QtSql>
#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "connexionview.h"
#include "compteview.h"
#include "databasemanager.h"

using namespace std;

int main(int countArg, char **listArg)
{
    QApplication app(countArg, listArg);

    DatabaseManager* dm = DatabaseManager::getInstance();

    if(dm->login())
    {
        ConnexionView* connexion = new ConnexionView;
        connexion->show();

        /*
        CompteView* compteview = new CompteView;
        compteview->show();
        */
    }

    return app.exec();
}
