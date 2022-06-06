#include "seconnecter.h"
#include "ui_seconnecter.h"
#include "database.h"
#include "chifoumivue.h"
#include <QDebug>

Seconnecter::Seconnecter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Seconnecter)
{
    ui->setupUi(this);
    connect(ui->boutConnexion, SIGNAL(clicked()), this, SLOT(valider()));

}

Seconnecter::~Seconnecter()
{
    delete ui;
}

void Seconnecter::valider()
{
    // Récupération du nom et du mot de passe
    utilisateur = ui->nomUtilisateur->text();
    motdepasse = ui->motDePasse->text();
    // Booléen permettant la vérification de la connexion vers le chifoumi
    bool connexionvalide = false;

    // Requête permettant de récupérer les valeurs
    QSqlQuery query;
    query.exec("SELECT * FROM ConnexionChifoumi");

    while (query.next()) {
        // Pour chaque ligne de résultat, on récupère la valeur d'index 1 et 2 -> utilisateur et motdepasse
        QString nomactuel = query.value(1).toString();
        QString mdpactuel = query.value(2).toString();

        if (nomactuel == utilisateur && mdpactuel == motdepasse) { // Si les noms concordent
            // Connexion trouvée
            connexionvalide = true;
            break;
        }
    }

    if (connexionvalide) { // Si la connexion est effectuée, on peut retourner à l'application
        close();
    } else { // Sinon, fenêtre avec message d'erreur
        QString err = "Erreur";
        QString libelleErr = "Nom d'utilisateur ou mot de passe invalide, veuillez réessayer.";
        QMessageBox::information(this, err, libelleErr);
    }




}
