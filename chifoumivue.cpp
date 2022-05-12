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

chifoumiVue::chifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chifoumiVue)
{
    ui->setupUi(this);
    connect(ui ->action_Quitter, SIGNAL(triggered()),this, SLOT(close()));              //Connexion avec l'option quitter dans l'onglet fichier
    connect(ui -> BoutNouvellePartie, SIGNAL(clicked()),this,SLOT(demarerPartie()));    //Connexion du bouton nouvelle partie avec le slot qui demarre la partie
    connect(ui -> BoutPierre,SIGNAL(clicked()),this,SLOT(coupPierre()));                //Connexion du bouton pierre avec le slot qui permet au joueur de jouer pierre
    connect(ui->BoutCiseaux,SIGNAL(clicked()),this,SLOT(coupCiseau()));                 //Connexion du bouton ciseau avec le slot qui permet au joueur de jouer ciseau
    connect(ui->BoutPapier,SIGNAL(clicked()),this,SLOT(coupPapier()));                  //Connexion du bouton papier avec le slot qui permet au joueur de jouer papier

}

chifoumiVue::~chifoumiVue()
{
    delete ui;
}

void chifoumiVue::demarerPartie()
{
    //Demarage d'une nouvelle partie
    int varChifoumiVue;
    varChifoumiVue = _laPresentation->reinitialiserPartie();

    ui -> ImageChoixUtili -> setPixmap(QPixmap(QString::fromUtf8(":/images/images/rien_115.png")));    //Remise à rien de l'affichage pour le joueur
    ui -> ImageChoixMachi -> setPixmap(QPixmap(QString::fromUtf8(":/images/images/rien_115.png")));    //Remise à rien de l'affichage pour le joueur
    ui -> ChoixFigure -> setEnabled(true);

    QString var;
    var = QString::number(varChifoumiVue);
    ui -> ScoreVous -> setText(var);

}

void chifoumiVue::coupPierre()
{
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/pierre_115.png")));
}

void chifoumiVue::coupCiseau()
{
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/ciseau_115.png")));
}

void chifoumiVue::coupPapier()
{
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/papier_115.png")));
}






