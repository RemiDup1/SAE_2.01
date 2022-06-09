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
    switch (etat)
    {
        case etatInitial:
            //maj de l'etat
            setEtat(partieEnCours);
        //activité 1
            //maj du modele
            getModele()->initScores();
            getModele()->initCoups();
            //Repercuter modele sur interface
            getVue()->afficherScoreJoueur(getModele()->getScoreJoueur());
            getVue()->afficherScoreMachine(getModele()->getScoreMachine());
            getVue()->afficherCoupJoueur(getModele()->getCoupJoueur());
            getVue()->afficherCoupMachine(getModele()->getCoupMachine());
            //Maj de l'interactivité de l'interface
            getVue()->majInterface(etat);

            break;
        case partieEnCours:
            //maj du modele
            getModele()->initScores();
            getModele()->initCoups();
            //Repercuter modele sur interface
            getVue()->afficherScoreJoueur(getModele()->getScoreJoueur());
            getVue()->afficherScoreMachine(getModele()->getScoreMachine());
            getVue()->afficherCoupJoueur(getModele()->getCoupJoueur());
            getVue()->afficherCoupMachine(getModele()->getCoupMachine());
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

}

void Presentation::setEtat(Presentation::UnEtatJeu e)
{
    etat = e;
}

Presentation::UnEtatJeu Presentation::getEtat()
{
    return etat;
}




