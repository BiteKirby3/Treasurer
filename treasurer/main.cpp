#include <QCoreApplication>
#include <QtSql>
#include <iostream>

#define q2c(string) string.toStdString()

using namespace std;

int main(int countArg, char **listArg) {
    QCoreApplication app(countArg, listArg);
    cout << flush;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("109.234.164.162");
    db.setUserName("belu0255_treasurer");
    db.setPassword("9fIDBY^PRH9J");
    db.setDatabaseName("belu0255_treasurer");
    if(db.open()) {
        cout << "Vous êtes maintenant connecté à " << q2c(db.hostName()) << endl;
        db.close();
    }
    else { cout << "La connexion a échouée, désolé : (" << q2c(db.lastError().text()) << ")" << endl; }

    return app.exec();
}
