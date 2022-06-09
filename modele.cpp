#include "modele.h"
#include "QDebug"

Modele::Modele()
{

}
Modele::UnCoup Modele::getCoupJoueur()
{
    return coupJoueur;
}

Modele::UnCoup Modele::getCoupMachine()
{
    return coupMachine;
}

unsigned int Modele::getScoreJoueur()
{
    return scoreJoueur;
}

unsigned int Modele::getScoreMachine()
{
    return scoreMachine;
}

char Modele::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';
    UnCoup joueur = getCoupJoueur();
    UnCoup machine = getCoupMachine();

    if (machine == UnCoup::papier && joueur == UnCoup::ciseau) {
        gagnantARetourner = 'J';
    }
    if (machine == UnCoup::papier && joueur == UnCoup::pierre) {
        gagnantARetourner = 'M';
    }
    if (machine == UnCoup::pierre && joueur == UnCoup::ciseau) {
        gagnantARetourner = 'M';
    }
    if (machine == UnCoup::pierre && joueur == UnCoup::papier) {
        gagnantARetourner = 'J';
    }
    if (machine == UnCoup::ciseau && joueur == UnCoup::pierre) {
        gagnantARetourner = 'J';
    }
    if (machine == UnCoup::ciseau && joueur == UnCoup::papier) {
        gagnantARetourner = 'M';
    }
    return gagnantARetourner;
}


void Modele::setCoupJoueur(UnCoup coupJ)
{
    if (coupJ == UnCoup::papier)
    {
        coupJoueur = UnCoup::papier;
    }
    if (coupJ == UnCoup::pierre)
    {
        coupJoueur = UnCoup::pierre;
    }
    if (coupJ == UnCoup::ciseau)
    {
        coupJoueur = UnCoup::ciseau;
    }
}

//Fonction permettant de determiner le score de la machine aléatoirement
int randMinMax(int min, int max)
{
     /*pré-condition : min<max, Le nbre aléatoire est compris entre [min, max[*/
    return rand()%(max-min) + min;
}

//fonction permettant d'indiquer le coup de la machine et de determiner le gagnant
void Modele::setCoupMachine()
{
    int num;
    num = randMinMax(1,4);

    if (num == 1)
    {
        coupMachine = UnCoup::papier;
    }
    if (num == 2)
    {
        coupMachine = UnCoup::pierre;
    }
    if (num == 3)
    {
        coupMachine = UnCoup::ciseau;
    }
}

void Modele::setScoreJoueur(unsigned int p_score)
{
    scoreJoueur = scoreJoueur + p_score;
}

void Modele::setScoreMachine(unsigned int p_score)
{
    scoreMachine = scoreMachine + p_score;
}

void Modele::majScores(char p_gagnant)
{
    if (p_gagnant == 'J')
    {
        setScoreJoueur(1);
    }
    if (p_gagnant == 'M')
    {
        setScoreMachine(1);
    }
}

void Modele::initScores()
{
    scoreJoueur = 0;
    scoreMachine = 0;
}

void Modele::initCoups()
{
    coupJoueur = rien;
    coupMachine = rien;
}

