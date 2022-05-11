#include "presentation.h"
#include "QDebug"

presentation::presentation()
{

}

void presentation::reinitialiserPartie()
{
    qDebug () << "init reinitialiser";

}


/*void presentation::deroulementPartie()
{
    qDebug() << "debut deroulement " << Qt::endl;
    char p_gagnant;
    setCoupMachine();
    p_gagnant = determinerGagnant();

    majScores(p_gagnant);
    qDebug() << "fin deroulement " << Qt::endl;
}
*/
