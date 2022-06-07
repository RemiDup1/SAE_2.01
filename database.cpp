/*
Corps de la classe de la base de données (V7)
Dernière modification : 07/06/2022
*/

#include "database.h"

// Lancement de la base de données
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

// Fermeture de la base de données
void Database::closeDataBase()
{
    mydb.close();
}

// Vérification de la base de données
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
