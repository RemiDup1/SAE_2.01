#ifndef PRESENTATION_H
#define PRESENTATION_H
/*
Header du fichier concernant la présentation (V2)
Dernière modification : 07/06/2022
*/


#include "modele.h"
#include "database.h"

class chifoumiVue;
class Presentation
{
public:
    enum UnEtatJeu {etatInitial, partieEnCours, partieEnPause}; // Ajout d'un état : partieEnPause (V5)

    Presentation();

    // V2 - Gestion de la partie
    void deroulementPartie();
    void demarrerPartie();
    void arreterPartie();

    // V2 - Getters / Setters
    void setModele(Modele * m);
    Modele * getModele();
    void setVue(chifoumiVue * v);
    chifoumiVue * getVue();
    void setEtat(UnEtatJeu e);
    UnEtatJeu getEtat();

    // V2 - Coups
    void coupPierre();
    void coupCiseau();
    void coupPapier();

    void coupMachine();
    void majScore(char p_gagnant);

    // V5 - Gestion du temps/compte a rebours
    void pausePartie();
    void tempsEcoule();


    // V6 - Gestion des paramètres
    void parametrer();

    // V6 - Variables des paramètres
    unsigned int paramTemps = LIMITE_TEMPS;
    unsigned int paramScore = SCORE_LIMITE;


private:
    UnEtatJeu etat; //état du jeu par rapport au diagramme E.T
    chifoumiVue *laVue; // Vue
    Modele *leModele; // Modèle
    Database *db; // Base de données (V7)
};

#endif // PRESENTATION_H
