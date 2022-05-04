/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe métier (= modèle) Chifoumi-v1
 **************************************************************/
#include "chifoumi.h"

#include <cstdlib>
#include <ctime>


    ///* ---- PARTIE MODèLE ---------------------------

Chifoumi::Chifoumi()
{
    //ctor
    // partie modèle
}

Chifoumi::~Chifoumi()
{
    //dtor
}

        /// Getters

Chifoumi::UnCoup Chifoumi::getCoupJoueur() {
	return coupJoueur;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return coupMachine;
}

unsigned int Chifoumi::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int Chifoumi::getScoreMachine() {
    return scoreMachine;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';
    UnCoup joueur = getCoupJoueur();
    UnCoup machine = getCoupMachine();

    if (machine == papier && joueur == ciseau) {
        gagnantARetourner = 'J';
    }
    if (machine == papier && joueur == pierre) {
        gagnantARetourner = 'M';
    }
    if (machine == pierre && joueur == ciseau) {
        gagnantARetourner = 'M';
    }
    if (machine == pierre && joueur == papier) {
        gagnantARetourner = 'J';
    }
    if (machine == ciseau && joueur == pierre) {
        gagnantARetourner = 'J';
    }
    if (machine == ciseau && joueur == papier) {
        gagnantARetourner = 'M';
    }
    return gagnantARetourner;
}

         ///* Méthodes utilitaires du Modèle

int randMinMax(int min, int max){
    /* pré-condition : min<max ;
       Le nbre aléatoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner

	valeurGeneree = UnCoup(randMinMax(0,2));
    return valeurGeneree;
}

        /// Setters

void Chifoumi::setCoupJoueur(UnCoup p_coup) {
    coupJoueur = p_coup;
}

void Chifoumi::setCoupMachine(UnCoup p_coup) {
    coupMachine = p_coup;
}

void Chifoumi::setScoreJoueur(unsigned int p_score) {
    scoreJoueur = scoreJoueur + p_score;
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
    scoreMachine = scoreMachine + p_score;
}

void Chifoumi::majScores(char p_gagnant) {
    if (p_gagnant == 'J') {
        setScoreJoueur(1);
    }
    if (p_gagnant == 'M') {
        setScoreMachine(1);
    }
}

void Chifoumi::initScores() {
    scoreJoueur = 0;
    scoreMachine = 0;
}

void Chifoumi::initCoups() {
    coupJoueur = rien;
    coupMachine = rien;
}
