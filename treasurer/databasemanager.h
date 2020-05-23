#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>


class DatabaseManager
{
public:
    bool login();
    void logout();
    QSqlDatabase getDatabase();
    static DatabaseManager* getInstance();

private:
    DatabaseManager() {};
    QSqlDatabase db;
    static DatabaseManager* dm;
};

#endif // DATABASEMANAGER_H
