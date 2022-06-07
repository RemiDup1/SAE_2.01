/*
Corps du fichier gérant la présentation de l'application
Dernière modification : 07/06/2022
*/

#include "presentation.h"
#include "chifoumivue.h"
#include "modele.h"
#include "database.h"

// Initialisation de la présentation
Presentation::Presentation()
{
    setEtat(etatInitial);
}

// Getters & Setters (V2)
void Presentation::setModele(Modele *m)
{
    leModele = m;
}
Modele *Presentation::getModele()
{
    return leModele;
}
void Presentation::setVue(chifoumiVue *v)
{
    laVue = v;
}
chifoumiVue *Presentation::getVue()
{
    return laVue;
}
void Presentation::setEtat(Presentation::UnEtatJeu e)
{
    etat = e;
}

Presentation::UnEtatJeu Presentation::getEtat()
{
    return etat;
}

// Procédure de démarrage de la partie (V2)
void Presentation::demarrerPartie()
{
    // Récupération des paramètres (V2 / V5)
    getModele()->initScores();
    getModele()->initCoups();
    // Mise à jour de la vie
    getVue()->afficherScoreJoueur(getModele()->getScoreJoueur());
    getVue()->afficherScoreMachine(getModele()->getScoreMachine());
    getVue()->afficherCoupJoueur(getModele()->getCoupJoueur());
    getVue()->afficherCoupMachine(getModele()->getCoupMachine());

    // Mise à jour de l'interface en fonction de l'état
    switch (etat)
    {
    case etatInitial:
        //maj de l'etat
        setEtat(partieEnCours);
        //Maj de l'interactivité de l'interface
        getVue()->majInterface(etat);
        break;
    case partieEnCours:
        break;
    default:
        break;
    }
}

// Procédure de démarrage de la partie (V2)
void Presentation::arreterPartie()
{
    // Récupération des scores du Joueur et de la Machine (V9)
    int scoreFinalJoueur = getModele()->getScoreJoueur();
    int scoreFinalMachine = getModele()->getScoreMachine();

    // Réinitialisation des Coups / Scores
    getModele()->initScores();
    getModele()->initCoups();

    // Mise à jour de la vue
    getVue()->afficherScoreJoueur(getModele()->getScoreJoueur());
    getVue()->afficherScoreMachine(getModele()->getScoreMachine());
    getVue()->afficherCoupJoueur(getModele()->getCoupJoueur());
    getVue()->afficherCoupMachine(getModele()->getCoupMachine());
    getVue()->tempsRestant = paramTemps; // Arrêt du compte à rebours et réinitialisation de ce dernier
    getVue()->compteARebours->stop();

    // Requête d'ajout du score dans la table récupérant les scores
    QSqlQuery query;
    query.prepare("INSERT INTO ScoresChifoumi (DateHeure, NomJoueur, ScoreJ, ScoreM) VALUES (CURRENT_TIMESTAMP(), ?, ?, ?)");
    query.addBindValue(getVue()->nomJoueur);
    query.addBindValue(scoreFinalJoueur);
    query.addBindValue(scoreFinalMachine);
    query.exec();

    // Mise à jour de l'interface en fonction de l'état
    switch (etat)
    {
    case partieEnCours:
        //maj de l'etat
        setEtat(etatInitial);
        //Maj de l'interactivité de l'interface
        getVue()->majInterface(etat);
        break;
    case etatInitial:
        break;
    default:
        break;
    }
}


// Procédure du déroulement de la partie
void Presentation::deroulementPartie()
{
    char p_gagnant;
    coupMachine();
    p_gagnant = getModele()->determinerGagnant();
    majScore(p_gagnant);
}

// Procédures des différents coups (V2)
void Presentation::coupPierre()
{
    switch (etat)
    {
        case etatInitial:
            break;
        case partieEnCours:
            getModele()->setCoupJoueur(Modele::pierre);
            getVue()->afficherCoupJoueur(getModele()->getCoupJoueur());
            deroulementPartie();
            break;
        default:
            break;
    }
}

void Presentation::coupCiseau()
{
    switch (etat)
    {
        case etatInitial:
            break;
        case partieEnCours:
            getModele()->setCoupJoueur(Modele::ciseau);
            getVue()->afficherCoupJoueur(getModele()->getCoupJoueur());
            deroulementPartie();
            break;
        default:
            break;
    }
}

void Presentation::coupPapier()
{
    switch (etat)
    {
        case etatInitial:
            break;
        case partieEnCours:
            getModele()->setCoupJoueur(Modele::papier);
            getVue()->afficherCoupJoueur(getModele()->getCoupJoueur());
            deroulementPartie();
            break;
        default:
            break;
    }
}

void Presentation::coupMachine()
{
    getModele()->setCoupMachine();
    getVue()->afficherCoupMachine(getModele()->getCoupMachine());
}

// Procédure de mise à jour des scores (V2)
void Presentation::majScore(char p_gagnant) // Mise à jour des scores et affichage des résultats en cas de limite de score atteinte
{
    getModele()->majScores(p_gagnant);
    switch (p_gagnant)
    {
        case 'M':
            getVue()->afficherScoreMachine(getModele()->getScoreMachine());
            break;
        case 'J':
            getVue()->afficherScoreJoueur(getModele()->getScoreJoueur());
            break;
        default:
            break;
    }

    if (getModele()->getScoreMachine() >= paramScore)
    {
        QMessageBox *messageFin = new QMessageBox;
        messageFin->setWindowTitle("Défaite...");
        messageFin->setText("Dommage ! La machine vous à vaincu en "+QString::number(paramTemps - getVue()->tempsRestant)+" secondes...");
        messageFin->show();
        arreterPartie();
    }
    else if (getModele()->getScoreJoueur() >= paramScore)
    {
        QMessageBox *messageFin = new QMessageBox;
        messageFin->setWindowTitle("Victoire !");
        messageFin->setText("Bravo ! Vous avez vaincu la machine en "+QString::number(paramTemps - getVue()->tempsRestant)+" secondes !");
        messageFin->show();
        arreterPartie();
    }
}

// Procédure de mise en pause de la partie (V5)
void Presentation::pausePartie()
{
    // Changement de l'interface en fonction de l'état actuel
    UnEtatJeu etatActuel = getEtat();
    if (etatActuel != partieEnPause) {
        setEtat(partieEnPause);
        getVue()->majInterface(etat);
    } else {
        setEtat(partieEnCours);
        getVue()->majInterface(etat);
    }
}

// Procédure si le temps est écoulé (V5)
void Presentation::tempsEcoule() // Affichage des résultats de la partie en cas de temps écoulé
{
    // Si le temps restant est inférieur ou égal à 0 :
    if (getVue()->tempsRestant <= 0) {
        // On récupère les scores
        int scoreFinalJoueur = getModele()->getScoreJoueur();
        int scoreFinalMachine = getModele()->getScoreMachine();
        // Affichage du gagnant en fonction des scores
        if (scoreFinalJoueur > scoreFinalMachine) {
                QMessageBox *messageFin = new QMessageBox;
                messageFin->setWindowTitle("Victoire !");
                messageFin->setText(" Le temps est écoulé !\n Cependant, vous avez fait mieux que la machine par un score de "+QString::number(scoreFinalJoueur)+" à "+QString::number(scoreFinalMachine));
                messageFin->show();
        } else if (scoreFinalJoueur < scoreFinalMachine) {
            QMessageBox *messageFin = new QMessageBox;
            messageFin->setWindowTitle("Défaite...");
            messageFin->setText(" Le temps est écoulé !\n Cependant, la machine a fait mieux que vous par un score de "+QString::number(scoreFinalJoueur)+" à "+QString::number(scoreFinalMachine));
            messageFin->show();
        } else {
            QMessageBox *messageFin = new QMessageBox;
            messageFin->setWindowTitle("Match-nul");
            messageFin->setText(" Le temps est écoulé !\n Cependant, vous avez fait match-nul par un score de "+QString::number(scoreFinalJoueur)+" à "+QString::number(scoreFinalMachine));
            messageFin->show();
        }
        arreterPartie(); // Arrêt de la partie
    }
}

// Procédure du paramétrage (V6)
void Presentation::parametrer()
{
    paramScore = getVue()->param->scoremax;
    paramTemps = getVue()->param->tempsmax;
    getVue()->nomJoueur = getVue()->param->nom;
}








