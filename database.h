#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QDebug>

#define DATABASE_NAME "R202"
#define CONNECT_TYPE "QODBC"


class Database
{
public:
    Database(){};
    bool openDataBase();
    void closeDataBase();
    void restoreDataBase();

private:
    QSqlDatabase mydb;

};

#endif // DATABASE_H
