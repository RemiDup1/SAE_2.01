#include "database.h"

bool Database::openDataBase()
{
   mydb = QSqlDatabase::addDatabase("QODBC");
   mydb.setHostName("lakartxela");
   mydb.setDatabaseName("R202");
   mydb.setUserName("tcdartiguelo_bd");
   mydb.setPassword("tcdartiguelo_bd");
   bool ouvert = mydb.open();
   return ouvert;
}

void Database::closeDataBase()
{
    mydb.close();
}

void Database::restoreDataBase()
{
    // Tentative de connexion
    bool connexionBase = mydb.isValid();
    if (connexionBase) {
        qDebug() << "Connexion à la base valide";
    }

    // Vérification de l'ouverture de la base
    bool baseOuverte = mydb.isOpen();
    if (baseOuverte) {
        qDebug() << "Base de données ouverte";

    }
}
