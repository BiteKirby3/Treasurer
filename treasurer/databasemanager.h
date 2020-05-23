#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>


class DatabaseManager
{
private:
    DatabaseManager() {};
    QSqlDatabase db;
    static DatabaseManager* dm;


public:
    bool login();
    void logout();
    QSqlDatabase getDatabase();
    static DatabaseManager* getInstance();
};

#endif // DATABASEMANAGER_H
