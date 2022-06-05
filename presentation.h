#ifndef PRESENTATION_H
#define PRESENTATION_H
#include "modele.h"

class chifoumiVue;
class Presentation
{
public:
    enum UnEtatJeu {etatInitial, partieEnCours, partieEnPause}; // Ajout d'un état : partieEnPause
    Presentation();
    void deroulementPartie();

    void setModele(Modele * m);
    Modele * getModele();

    void setVue(chifoumiVue * v);
    chifoumiVue * getVue();

    void demarrerPartie();
    void arreterPartie();
    void pausePartie();
    void tempsEcoule();
    void coupPierre();
    void coupCiseau();
    void coupPapier();
    void coupMachine();
    void majScore(char p_gagnant);

    unsigned int paramTemps = LIMITE_TEMPS;
    unsigned int paramScore = SCORE_LIMITE;

    void setEtat(UnEtatJeu e);
    UnEtatJeu getEtat();

private:
    UnEtatJeu etat; //état du jeu par rapport au diagramme E.T
    chifoumiVue *laVue;
    Modele *leModele;
};

#endif // PRESENTATION_H
