#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H
/*
Header du fichier concernant la vue de l'application
Dernière modification : 07/06/2022
*/

// Importation des modules utilisées
#include <QMainWindow> // V2
#include <QDebug> // V2
#include <QDialog> // V3
#include <QMessageBox> // V3
#include <QTimer> // V5

// Importation des autres classes utilisées
#include "modele.h" // V2
#include "presentation.h" // V2
#include "parametres.h" // V6
#include "database.h" // V7
#include "seconnecter.h" // V7
#include "topscores.h" // V9


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

    // V2 - Getter / Setter
    void setPresentation(Presentation *p);
    Presentation * getPresentation();

    // V2 - Affichage des différents attributs des joueurs (coup / score)
    void afficherScoreJoueur(unsigned int scoreJ);
    void afficherScoreMachine(unsigned int scoreM);
    void afficherCoupJoueur(Modele::UnCoup coupJ);
    void afficherCoupMachine(Modele::UnCoup coupM);

    // V2 - Mise à jour de l'interface
    void majInterface(Presentation::UnEtatJeu e);
    QString afficherNomCoup (Modele::UnCoup c);

    // V4
    void setLimiteScore(int scorePT);

    // V5 - Création du compte à rebours
    QTimer *compteARebours = new QTimer(this); // Objet de la classe QTimer pour faire le compte à rebours
    int tempsRestant; // Initialisation d'un nombre entier représentant le temps restant

    // V6 - Création des paramètres de jeu
    Parametres *param;
    QString nomJoueur = "Vous";

    // V7 - Création de la connexion à l'application
    Seconnecter *connexion;

    // V9 - Création de l'affichage des meilleurs scores
    TopScores *scores;

private slots:

    // V2 - Slots pour la gestion de la parties
    void demarrerPartie();
    void arreterPartie();

    // V2 - Slots pour la gestion des coups
    void coupPierre();
    void coupCiseau();
    void coupPapier();

    // V3 - Slot pour l'affichage du à propos
    void aProposDe();

    // V5 - Slots pour la gestion du compte à rebours
    void decompte(); // Slot pour le décompte du temps
    void pause(); // Slot pour mettre le jeu en pause

    // V6 - Slot pour le paramétrage de la partie
    void parametrage();

    // V9 - Slot pour l'affichage des meilleurs scores
    void topScores();

///* Attributs du Modèle
private:

    // Ajoutés en V2
    Presentation *laPresentation;
    Ui::chifoumiVue *ui;

    // Ajoutés en V7
    Database *db; // Base de données


};
#endif // CHIFOUMIVUE_H
