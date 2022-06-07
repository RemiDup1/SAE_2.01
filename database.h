#ifndef DATABASE_H
#define DATABASE_H
/*
Header du fichier concernant la création / gestion de la base de données (V7)
Dernière modification : 07/06/2022
*/


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
