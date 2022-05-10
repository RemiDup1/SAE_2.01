#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class chifoumiVue; }
QT_END_NAMESPACE

class chifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    chifoumiVue(QWidget *parent = nullptr);
    ~chifoumiVue();

private slots:
    void demarerPartie();           //Slot pour commencer la partie
    void coupPierre();              //slot pour le coup Pierre
    void coupCiseau();              //slot pour le coup ciseau
    void coupPapier();              //slot pour le coup papier
    void coupMachine(int);          //slot pour le coup effectuer par la machine

private:
    Ui::chifoumiVue *ui;
    int randMinMax(int, int);       //fonction qui génère un nombre aléatoire
    char determineGagnat(int,int);  //Fonction qui determine le gagnant entre le joueur et la machine
};
#endif // CHIFOUMIVUE_H
