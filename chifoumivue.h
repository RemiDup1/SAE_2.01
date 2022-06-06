#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QTimer>

#include "modele.h"
#include "presentation.h"
#include "parametres.h"
#include "seconnecter.h"



QT_BEGIN_NAMESPACE
namespace Ui { class chifoumiVue; }
QT_END_NAMESPACE

class Presentation;
class chifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    chifoumiVue(QWidget *parent = nullptr);
    ~chifoumiVue();

    void setPresentation(Presentation *p);
    Presentation * getPresentation();

    void afficherScoreJoueur(unsigned int scoreJ);
    void afficherScoreMachine(unsigned int scoreM);
    void afficherCoupJoueur(Modele::UnCoup coupJ);
    void afficherCoupMachine(Modele::UnCoup coupM);

    void majInterface(Presentation::UnEtatJeu e);
    QString afficherNomCoup (Modele::UnCoup c);

    void setLimiteScore(int scorePT);

    QTimer *compteARebours = new QTimer(this); // Objet de la classe QTimer pour faire le compte à rebours
    int tempsRestant; // Initialisation d'un nombre entier représentant le temps restant

    Parametres *param;
    QString nomJoueur = "Vous";

    Seconnecter *connexion;
    Database *db;



private slots:
    void demarrerPartie();
    void arreterPartie();
    void coupPierre();
    void coupCiseau();
    void coupPapier();
    void aProposDe();
    void decompte(); // Slot pour le décompte du temps
    void pause(); // Slot pour mettre le jeu en pause
    void parametrage();

///* Attributs du Modèle
private:
    Presentation *laPresentation;
    Ui::chifoumiVue *ui;



};
#endif // CHIFOUMIVUE_H
