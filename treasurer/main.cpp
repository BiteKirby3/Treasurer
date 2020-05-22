#include <QCoreApplication>
#include <QtSql>
#include <iostream>

#define q2c(string) string.toStdString()

using namespace std;

int main(int countArg, char **listArg) {
    QCoreApplication app(countArg, listArg);
    cout << flush;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("*********");
    db.setUserName("*********");
    db.setPassword("*********");
    db.setDatabaseName("*********");
    if(db.open()) {
        cout << "Vous etes maintenant connecte a " << q2c(db.hostName()) << endl;
        db.close();
    }
    else { cout << "La connexion a echouee, desole : (" << q2c(db.lastError().text()) << ")" << endl; }

    return app.exec();
}
