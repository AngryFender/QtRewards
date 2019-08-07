#include "database.h"

database::database()
{
    //check for the QSQLITE  driver
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER))
        qDebug() << "QSQLITE driver missing";


    //open database file
    QSqlDatabase database = QSqlDatabase::addDatabase(DRIVER);
    QString DatabaseLocation = QCoreApplication::applicationDirPath()+"/accounts.db";
    database.setDatabaseName(DatabaseLocation);
    if(!database.open())
        qDebug()<< ".db file missing or could not be opened";


    //abstract data from the database into QSqlQueryModel
    QSqlQuery query_accounts(database);
    QSqlQuery query_channelsRewards(database);

    query_accounts.exec("SELECT * from accounts");
    query_channelsRewards.exec("SELECT * from channelsRewards");

    sqlAccounts        = new QSqlQueryModel();
    sqlChannelsRewards = new QSqlQueryModel();

    sqlAccounts->setQuery(query_accounts);
    sqlChannelsRewards->setQuery(query_channelsRewards);
}

database::~database()
{
    delete sqlAccounts;
    delete sqlChannelsRewards;
}

QSqlQueryModel *database::getSqlAccounts() const
{
    return sqlAccounts;
}

QSqlQueryModel *database::getSqlChannelsRewards() const
{
    return sqlChannelsRewards;
}
