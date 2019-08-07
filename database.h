#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCoreApplication>
#include <QSqlRecord>

class database
{
public:
    database();
    ~database();
    QSqlQueryModel *getSqlAccounts() const;
    QSqlQueryModel *getSqlChannelsRewards() const;

private:
    QSqlQueryModel *sqlAccounts ;
    QSqlQueryModel *sqlChannelsRewards ;
};

#endif // DATABASE_H
