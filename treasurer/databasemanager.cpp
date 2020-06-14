#include "databasemanager.h"

bool DatabaseManager::login()
{
    this->db = QSqlDatabase::addDatabase("QPSQL");
    this->db.setPort(5432);
    this->db.setHostName("localhost");
    this->db.setUserName("postgres");
    this->db.setPassword("Mathilde");
    this->db.setDatabaseName("postgres");

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
    if (!dm)
    {
        dm = new DatabaseManager();
    }

    return dm;
}

DatabaseManager* DatabaseManager::dm = nullptr;
