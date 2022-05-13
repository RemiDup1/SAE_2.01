/*
 * Programme du chifoumi
 * Version 1 du programme
 * Date dernier modification : 09/05/2022
 * auteur : Remi Dupin
 *
*/
#include "chifoumivue.h"
#include "ui_chifoumivue.h"
#include "presentation.h"
#include "qdebug.h"
#include "modele.h"

chifoumiVue::chifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chifoumiVue)
{
    ui->setupUi(this);
    connect(ui ->action_Quitter, SIGNAL(triggered()),this, SLOT(close()));              //Connexion avec l'option quitter dans l'onglet fichier
    connect(ui -> BoutNouvellePartie, SIGNAL(clicked()),this,SLOT(demarrerPartie()));    //Connexion du bouton nouvelle partie avec le slot qui demarre la partie
    connect(ui -> BoutPierre,SIGNAL(clicked()),this,SLOT(coupPierre()));                //Connexion du bouton pierre avec le slot qui permet au joueur de jouer pierre
    connect(ui->BoutCiseaux,SIGNAL(clicked()),this,SLOT(coupCiseau()));                 //Connexion du bouton ciseau avec le slot qui permet au joueur de jouer ciseau
    connect(ui->BoutPapier,SIGNAL(clicked()),this,SLOT(coupPapier()));                  //Connexion du bouton papier avec le slot qui permet au joueur de jouer papier


}

chifoumiVue::~chifoumiVue()
{
    delete ui;
}

void chifoumiVue::setPresentation(Presentation *p)
{
    laPresentation = p;
}

Presentation *chifoumiVue::getPresentation()
{
    return laPresentation;
}

void chifoumiVue::afficherScoreJoueur(unsigned int scoreJ)
{
    qDebug () << "chifoumiVue : J'affiche score joueur = " << scoreJ << Qt::endl;
}

void chifoumiVue::afficherScoreMachine(unsigned int scoreM)
{
    qDebug () << "chifoumiVue : J'affiche score machine = " << scoreM << Qt::endl;
}

void chifoumiVue::afficherCoupJoueur(Modele::UnCoup coupJ)
{
    //QString
    qDebug () << "chifoumiVue : coup Joueur  = " << afficherNomCoup(coupJ) << Qt::endl;
}

void chifoumiVue::afficherCoupMachine(Modele::UnCoup coupM)
{
    qDebug () << "chifoumiVue : coup Machine  = " << afficherNomCoup(coupM) << Qt::endl;
}

void chifoumiVue::majInterface(Presentation::UnEtatJeu e)
{
    switch (e)
    {
        case Presentation::etatInitial:
            ui -> ChoixFigure -> setEnabled(false);
            ui ->BoutNouvellePartie -> setEnabled(true);
            ui ->BoutNouvellePartie->setFocus();
            break;
        case Presentation::partieEnCours:
            ui -> ChoixFigure -> setEnabled(true);
            ui ->BoutNouvellePartie -> setEnabled(true);
            ui ->BoutNouvellePartie->setFocus();
            break;
        default:
            break;
    }
}

QString chifoumiVue::afficherNomCoup(Modele::UnCoup c)
{
  QString chaine ="";
  switch (c)
  {
    case Modele::rien:
      chaine = "rien";
      break;
    case Modele::pierre:
        chaine = "pierre";
        break;
    case Modele::papier:
        chaine = "papier";
        break;
    case Modele::ciseau:
        chaine = "ciseau";
        break;
    default:
        chaine = "";
        break;
    }
  return  chaine;
}

void chifoumiVue::demarrerPartie()
{
    getPresentation()->demarrerPartie();



    /*
    //Demarage d'une nouvelle partie
    int varChifoumiVue;
    varChifoumiVue = laPresentation->reinitialiserPartie();
    //laPresentation->deroulementPartie();


    ui -> ImageChoixUtili -> setPixmap(QPixmap(QString::fromUtf8(":/images/images/rien_115.png")));    //Remise à rien de l'affichage pour le joueur
    ui -> ImageChoixMachi -> setPixmap(QPixmap(QString::fromUtf8(":/images/images/rien_115.png")));    //Remise à rien de l'affichage pour le joueur
    ui -> ChoixFigure -> setEnabled(true);

    QString var;
    var = QString::number(varChifoumiVue);
    ui -> ScoreVous -> setText(var);
    */
}

void chifoumiVue::coupPierre()
{
    getPresentation()->coupPierre();

    //ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/pierre_115.png")));
}

void chifoumiVue::coupCiseau()
{
    getPresentation()->coupCiseau();
    //ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/ciseau_115.png")));
}

void chifoumiVue::coupPapier()
{
    getPresentation()->coupPapier();
    //ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/papier_115.png")));
}






