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

void Presentation::majScore(char p_gagnant)
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

    if (getModele()->getScoreMachine() >= SCORE_LIMITE)
    {
        arreterPartie();
        QMessageBox *messageFin = new QMessageBox;
        messageFin->setWindowTitle("Fin de la partie");
        messageFin->setText("Perdu ! Vous avez perdu contre la machine !");
        messageFin->show();
    }
    else if ( getModele()->getScoreJoueur() >= SCORE_LIMITE )
    {
        arreterPartie();
        QMessageBox *messageFin = new QMessageBox;
        messageFin->setWindowTitle("Fin de la partie");
        messageFin->setText("Bravo, vous avez gagné contre la machine !");
        messageFin->show();
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






