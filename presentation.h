#ifndef PRESENTATION_H
#define PRESENTATION_H
#include "modele.h"

class ChifoumiVue;
class presentation
{
public:
    presentation();
    int reinitialiserPartie();
    void deroulementPartie();
    void majInterface();

private:
    ChifoumiVue *_laVue;
    modele *_leModele;
};

#endif // PRESENTATION_H
