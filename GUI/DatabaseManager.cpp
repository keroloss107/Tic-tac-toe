#include "DatabaseManager.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>

DatabaseManager::DatabaseManager()
{
    // Use standard application data location
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/TicTacToe";
    QDir().mkpath(dataDir);  // Ensure directory exists

    QString dbPath = dataDir + "/appdata.db";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    qDebug() << "[DatabaseManager] Using DB file at:" << dbPath;
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connect()
{
    if (!db.isOpen()) {
        if (!db.open()) {
            qWarning() << "[DatabaseManager] Failed to open database:" << db.lastError().text();
            return false;
        }
        else {
            qDebug() << "[DatabaseManager] Database connected successfully.";
        }
    }

    return createTables();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    bool usersTable = query.exec(R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        );
    )");

    bool historyTable = query.exec(R"(
    CREATE TABLE IF NOT EXISTS history (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        player TEXT NOT NULL,
        opponent TEXT NOT NULL,
        result TEXT NOT NULL,
        date TEXT NOT NULL
    );
)");


    if (!usersTable || !historyTable) {
        qWarning() << "[DatabaseManager] Failed to create tables:" << query.lastError().text();
    }

    return usersTable && historyTable;
}

bool DatabaseManager::registerUser(const QString& username, const QString& password)
{
    if (!connect()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash) VALUES (?, ?)");
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    query.addBindValue(username);
    query.addBindValue(hash.toHex());

    if (!query.exec()) {
        qWarning() << "[DatabaseManager] Register failed:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::loginUser(const QString& username, const QString& password)
{
    if (!connect()) return false;

    QSqlQuery query;
    query.prepare("SELECT password_hash FROM users WHERE username = ?");
    query.addBindValue(username);

    if (query.exec() && query.next()) {
        QString storedHash = query.value(0).toString();
        QByteArray enteredHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
        return storedHash == enteredHash;
    }
    else {
        qWarning() << "[DatabaseManager] Login query failed:" << query.lastError().text();
    }

    return false;
}

void DatabaseManager::saveGameResult(const QString& player, const QString& opponent, const QString& result)
{
    if (!connect()) {
        qWarning() << "[DatabaseManager] Can't save game result because database isn't open.";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO history (player, opponent, result, date) VALUES (?, ?, ?, ?)");
    query.addBindValue(player);
    query.addBindValue(opponent);
    query.addBindValue(result);
    query.addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));

    if (!query.exec()) {
        qWarning() << "[DatabaseManager] Failed to insert game result:" << query.lastError().text();
    }
    else {
        qDebug() << "[DatabaseManager] Game result saved for player:" << player << "vs" << opponent;
    }
}


QList<QVariantMap> DatabaseManager::getGameHistory(const QString& player)
{
    QList<QVariantMap> historyList;

    if (!connect()) {
        qWarning() << "[DatabaseManager] Can't load history because database isn't open.";
        return historyList;
    }

    QSqlQuery query;
    query.prepare("SELECT result, opponent, date FROM history WHERE player = ? ORDER BY date DESC");
    query.addBindValue(player);

    if (query.exec()) {
        while (query.next()) {
            QVariantMap entry;
            entry["result"] = query.value("result").toString();
            entry["opponent"] = query.value("opponent").toString();
            entry["date"] = query.value("date").toString();
            historyList.append(entry);
        }
        qDebug() << "[DatabaseManager] Loaded" << historyList.size() << "history entries for player:" << player;
    }
    else {
        qWarning() << "[DatabaseManager] Failed to get history:" << query.lastError().text();
    }

    return historyList;
}
