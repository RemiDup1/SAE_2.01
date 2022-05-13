#include "presentation.h"
#include "QDebug"
#include "chifoumivue.h"

Presentation::Presentation()
{
    setEtat(etatInitial);

}


int Presentation::reinitialiserPartie()
{
    return 0;

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
    qDebug () << "presentation: nouvelle partie demandée " << Qt::endl;
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
            break;
        default:
            break;
    }
}

void Presentation::coupPierre()
{
    qDebug () << "presentation: bouton Pierre cliqué " << Qt::endl;
    switch (etat)
    {
        case etatInitial:
            break;
        case partieEnCours:
            break;
        default:
            break;
    }
}

void Presentation::coupCiseau()
{
    qDebug () << "presentation: bouton Ciseau cliqué " << Qt::endl;
    switch (etat)
    {
        case etatInitial:
            break;
        case partieEnCours:
            break;
        default:
            break;
    }
}

void Presentation::coupPapier()
{
    qDebug () << "presentation: bouton Papier cliqué " << Qt::endl;
    switch (etat)
    {
        case etatInitial:
            break;
        case partieEnCours:
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


/*

void Presentation::deroulementPartie()
{
    qDebug() << "debut deroulement " << Qt::endl;
    char p_gagnant;
    setCoupMachine();
    p_gagnant = determinerGagnant();

    majScores(p_gagnant);
    qDebug() << "fin deroulement " << Qt::endl;
}

*/
