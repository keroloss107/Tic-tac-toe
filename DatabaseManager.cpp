#include "DatabaseManager.h"
#include <QCryptographicHash>
#include <QDateTime>

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("appdata.db");
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connect()
{
    if (!db.open())
        return false;
    return createTables();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    return query.exec(R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        );
    )") && query.exec(R"(
        CREATE TABLE IF NOT EXISTS history (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            player TEXT NOT NULL,
            result TEXT NOT NULL,
            date TEXT NOT NULL
        );
    )");
}

bool DatabaseManager::registerUser(const QString& username, const QString& password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash) VALUES (?, ?)");
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    query.addBindValue(username);
    query.addBindValue(hash.toHex());
    return query.exec();
}

bool DatabaseManager::loginUser(const QString& username, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT password_hash FROM users WHERE username = ?");
    query.addBindValue(username);
    if (query.exec() && query.next())
    {
        QString storedHash = query.value(0).toString();
        QByteArray enteredHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
        return storedHash == enteredHash;
    }
    return false;
}

void DatabaseManager::saveGameResult(const QString& player, const QString& result)
{
    QSqlQuery query;
    query.prepare("INSERT INTO history (player, result, date) VALUES (?, ?, ?)");
    query.addBindValue(player);
    query.addBindValue(result);
    query.addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
    query.exec();
}

