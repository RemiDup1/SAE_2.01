#include "chifoumivue.h"
#include "presentation.h"
#include "modele.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    chifoumiVue w;
    Presentation *p = new Presentation();
    Modele *m = new Modele();


    w.setPresentation(p);
    p->setModele(m);
    p->setVue(&w);
    w.show();
    return a.exec();
}
