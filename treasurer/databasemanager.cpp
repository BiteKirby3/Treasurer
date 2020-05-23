#include "databasemanager.h"

bool DatabaseManager::login()
{
    this->db = QSqlDatabase::addDatabase("QPSQL");
    this->db.setHostName("***");
    this->db.setUserName("***");
    this->db.setPassword("***");
    this->db.setDatabaseName("***");

    return this->db.open();
}

void DatabaseManager::logout()
{
    this->db.close();
}

QSqlDatabase DatabaseManager::getDatabase()
{
    return this->db;
}

DatabaseManager* DatabaseManager::getInstance()
{
    if (!dm) {
        dm = new DatabaseManager();
    }

    return dm;
}

DatabaseManager* DatabaseManager::dm = nullptr;
