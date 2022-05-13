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
    qDebug() << "Debut determiner gagnant " << Qt::endl;
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';
    UnCoup joueur = getCoupJoueur();
    UnCoup machine = getCoupMachine();

    qDebug () << machine << " " << joueur ;
    if (machine == UnCoup::papier && joueur == UnCoup::ciseau) {
        gagnantARetourner = 'J';
        qDebug() << "Cas 1 " << Qt::endl;
    }
    if (machine == UnCoup::papier && joueur == UnCoup::pierre) {
        gagnantARetourner = 'M';
        qDebug() << "Cas 2 " << Qt::endl;
    }
    if (machine == UnCoup::pierre && joueur == UnCoup::ciseau) {
        gagnantARetourner = 'M';
        qDebug() << "Cas 3 " << Qt::endl;
    }
    if (machine == UnCoup::pierre && joueur == UnCoup::papier) {
        gagnantARetourner = 'J';
        qDebug() << "Cas 4 " << Qt::endl;
    }
    if (machine == UnCoup::ciseau && joueur == UnCoup::pierre) {
        gagnantARetourner = 'J';
        qDebug() << "Cas 5 " << Qt::endl;
    }
    if (machine == UnCoup::ciseau && joueur == UnCoup::papier) {
        gagnantARetourner = 'M';
        qDebug() << "Cas 6 " << Qt::endl;
    }
    qDebug() << "Fin determiner gagnant " << Qt::endl;
    return gagnantARetourner;
}


//Fonction permettant de determiner le score de la machine aléatoirement
int randMinMax(int min, int max)
{
     /*pré-condition : min<max, Le nbre aléatoire est compris entre [min, max[*/
    return rand()%(max-min) + min;
}


void Modele::setCoupJoueur(int num)
{
    qDebug () << num << Qt::endl;
    if (num == 1)
    {
        qDebug () << "init papier";
        coupJoueur = UnCoup::papier;
    }
    if (num == 2)
    {
        coupJoueur = UnCoup::pierre;
    }
    if (num == 3)
    {
        coupJoueur = UnCoup::ciseau;
    }

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
        qDebug() << "gagnant joueur " << Qt::endl;
        setScoreJoueur(1);

    }
    if (p_gagnant == 'M')
    {
        qDebug() << "gagnant machine " << Qt::endl;
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

int Modele::test()
{
    int var = 16 ;
    qDebug () << "Modele.cpp, fonction test initialisé" << Qt::endl;
    return var;
    qDebug () << "Modele.cpp, fonction test fin de tache" << Qt::endl;

}

