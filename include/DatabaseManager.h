#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>



class DatabaseManager
{
public:
    static DatabaseManager& instance();
    bool connect();
    bool createTables();

    bool registerUser(const QString& username, const QString& password);
    bool loginUser(const QString& username, const QString& password);
    void saveGameResult(const QString& player, const QString& opponent, const QString& result);
    QList<QVariantMap> getGameHistory(const QString& player);

private:
    DatabaseManager();
    QSqlDatabase db;
};
#pragma once
