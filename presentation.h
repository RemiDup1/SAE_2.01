#ifndef PRESENTATION_H
#define PRESENTATION_H
#include "modele.h"

class chifoumiVue;
class Presentation
{
public:
    enum UnEtatJeu {etatInitial, partieEnCours};
    Presentation();
    int reinitialiserPartie();
    void deroulementPartie();
    void majInterface();

    void setModele(Modele * m);
    Modele * getModele();

    void setVue(chifoumiVue * v);
    chifoumiVue * getVue();

    void demarrerPartie();
    void coupPierre();
    void coupCiseau();
    void coupPapier();

    void setEtat(UnEtatJeu e);
    UnEtatJeu getEtat();

private:
    UnEtatJeu etat; //état du jeu par rapport au diagramme E.T
    chifoumiVue *laVue;
    Modele *leModele;
};

#endif // PRESENTATION_H
