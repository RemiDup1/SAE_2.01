#include "presentation.h"
#include "QDebug"
#include "chifoumivue.h"
#include "modele.h"

Presentation::Presentation()
{
    setEtat(etatInitial);

}

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

void Presentation::demarrerPartie()
{
    //maj du modele
    getModele()->initScores();
    getModele()->initCoups();
    //Repercuter modele sur interface
    getVue()->afficherScoreJoueur(getModele()->getScoreJoueur());
    getVue()->afficherScoreMachine(getModele()->getScoreMachine());
    getVue()->afficherCoupJoueur(getModele()->getCoupJoueur());
    getVue()->afficherCoupMachine(getModele()->getCoupMachine());

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

void Presentation::arreterPartie()
{
    //maj du modele
    getModele()->initScores();
    getModele()->initCoups();
    //Repercuter modele sur interface
    getVue()->afficherScoreJoueur(getModele()->getScoreJoueur());
    getVue()->afficherScoreMachine(getModele()->getScoreMachine());
    getVue()->afficherCoupJoueur(getModele()->getCoupJoueur());
    getVue()->afficherCoupMachine(getModele()->getCoupMachine());
    getVue()->tempsRestant = paramTemps; // Arrêt du compte à rebours et réinitialisation de ce dernier
    getVue()->compteARebours->stop();

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

void Presentation::pausePartie()
{
    UnEtatJeu etatActuel = getEtat();
    if (etatActuel != partieEnPause) {
        setEtat(partieEnPause);
        getVue()->majInterface(etat);
    } else {
        setEtat(partieEnCours);
        getVue()->majInterface(etat);
    }

}

void Presentation::tempsEcoule() // Affichage des résultats de la partie en cas de temps écoulé
{
    if (getVue()->tempsRestant <= 0) {
        int scoreFinalJoueur = getModele()->getScoreJoueur();
        int scoreFinalMachine = getModele()->getScoreMachine();
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
        arreterPartie();
    }
}

void Presentation::deroulementPartie()
{
    char p_gagnant;
    coupMachine();
    p_gagnant = getModele()->determinerGagnant();
    majScore(p_gagnant);
}

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
    else if ( getModele()->getScoreJoueur() >= paramScore)
    {
        QMessageBox *messageFin = new QMessageBox;
        messageFin->setWindowTitle("Victoire !");
        messageFin->setText("Bravo ! Vous avez vaincu la machine en "+QString::number(paramTemps - getVue()->tempsRestant)+" secondes !");
        messageFin->show();
        arreterPartie();
    }
}

void Presentation::setEtat(Presentation::UnEtatJeu e)
{
    etat = e;
}

Presentation::UnEtatJeu Presentation::getEtat()
{
    return etat;
}






