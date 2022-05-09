/*
 * Programme du chifoumi
 * Version 1 du programme
 * Date dernier modification : 09/05/2022
 * auteur : Remi Dupin
 *
*/
#include "chifoumivue.h"
#include "ui_chifoumivue.h"
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
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/rien_115.png")));    //Remise à rien de l'affichage pour le joueur
    ui ->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/rien_115.png")));    //Remise à rien de l'affichage pour le joueur
    ui ->ChoixFigure->setEnabled(true);                                                             //Activation des boutons pour le choix de la figure
    ui ->ScoreVous->setText("0");                                                                   //Remise à 0 du score du joueur
    ui ->ScoreMachine->setText("0");                                                                //Remise à 0 du score de la machine
}

//Quand le joueur joue pierre
void chifoumiVue::coupPierre()
{
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/pierre_115.png")));  //Affichage de l'image pierre dans la zone du coup du joueur
    int coupJoueur = 1;                                                                             //nombre qui permet d'indiquer quel coup a fait le joueur [1 = pierre]
    coupMachine(coupJoueur);                                                                        //Appel du programme permettant de faire le coup de la machine
}

//Quand le joueur joue ciseau
void chifoumiVue::coupCiseau()
{
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/ciseau_115.png")));  //Affichage de l'image ciseau dans la zone du coup du joueur
    int coupJoueur = 2;                                                                             //nombre qui permet d'indiquer quel coup a fait le joueur [2 = ciseau]
    coupMachine(coupJoueur);                                                                        //Appel du programme permettant de faire le coup de la machine
}

//Quand le joueur joue papier
void chifoumiVue::coupPapier()
{
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/papier_115.png")));  //Affichage de l'image papier dans la zone du coup du joueur
    int coupJoueur = 3;                                                                             //nombre qui permet d'indiquer quel coup a fait le joueur [3 = papier]
    coupMachine(coupJoueur);                                                                        //Appel du programme permettant de faire le coup de la machine
}

//fonction permettant d'indiquer le coup de la machine et de determiner le gagnant
void chifoumiVue::coupMachine(int numJoueur)
{
    char resu = 'E';                //Variables contenant une lettre pour determiner qui gagne
    QString valMachineScore;        //Decalarartion d'un variable QString pour contenir la valeur du score de la machine
    QString valJoueurScore;         //Decalarartion d'un variable QString pour contenir la valeur du score du joueur

    int numMachine = randMinMax(1,4);               //fonction permettant de determiner le coup de la machine de maniere aléatoire
    resu = determineGagnat(numJoueur,numMachine);   //fonction permettant de determiner qui a gagner entre le joueur et la machine

    if (resu == 'M')    //Le cas ou la machine gagne
    {
        valMachineScore = ui ->ScoreMachine->text();    //Récuperation du score de la machine se trouvant dans le Label ScoreMachine pour le mettre dans valMachineScore
        int num = valMachineScore.toInt();              //On le transforme le score en INT et on le stock dans num pour pouvoir le manipuler
        num ++;                                         //On incremente num de 1 le Score
        valMachineScore = QString::number(num);         //On transforme num en STRING et on stocke le score dans valMachineScore pour pouvoir l'afficher
        ui->ScoreMachine->setText(valMachineScore);     //On Met dans le Label ScoreMachine la valeur contenue dans valMachineScore
    }
    if(resu =='J')      //Le cas ou le joueur gagne
    {
        valJoueurScore = ui->ScoreVous->text();         //Récuperation du score du joueur se trouvant dans le Label ScoreVous pour le mettre dans valJoueurScore
        int num = valJoueurScore.toInt();               //On le transforme le score en INT et on le stock dans num pour pouvoir le manipuler
        num ++;                                         //On incremente num de 1 le Score
        valJoueurScore = QString::number(num);          //On transforme num en STRING et on stocke le score dans valJoueurScore pour pouvoir l'affichert
        ui->ScoreVous->setText(valJoueurScore);         //On Met dans le Label ScoreVous la valeur contenue dans valJoueurScore
    }
}

int chifoumiVue::randMinMax(int min, int max)       //Fonction permettant de determiner le score de la machine aléatoirement
{
     /*pré-condition : min<max, Le nbre aléatoire est compris entre [min, max[*/
    return rand()%(max-min) + min;
}

char chifoumiVue::determineGagnat(int joueur, int machine)      //Fonction qui permet de dertimener qui gagner entre le joueur et la machine
{
    char gagnantARetourner = 'E';

    if (machine == 1)       //Affichage de l'image pierre dans la zone du coup de machine
    {
        ui ->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/pierre_115.png")));
    }
    if (machine == 2)       //Affichage de l'image ciseau dans la zone du coup de machine
    {
        ui ->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/ciseau_115.png")));
    }
    if (machine == 3)       //Affichage de l'image joueur dans la zone du coup de machine
    {
        ui ->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/papier_115.png")));
    }


    if (machine == 3 && joueur == 2)    //cas où si le joueur joue ciseau et la machine papier
    {
        gagnantARetourner = 'J';        //Le joueur gagne
    }
    if (machine == 3 && joueur == 1)    //cas où si le joueur joue pierre et la machine papier
    {
        gagnantARetourner = 'M';        //La machine gagne
    }
    if (machine == 1 && joueur == 2)    //cas où si le joueur joue ciseau et la machine pierre
    {
        gagnantARetourner = 'M';        //La machine gagne
    }
    if (machine == 1 && joueur == 3)    //cas où si le joueur joue papier et la machine pierre
    {
        gagnantARetourner = 'J';        //Le joueur gagne
    }
    if (machine == 2 && joueur == 1)    //cas où si le joueur joue pierre et la machine ciseau
    {
        gagnantARetourner = 'J';        //Le joueur gagne
    }
    if (machine == 2 && joueur == 3)    //cas où si le joueur joue papier et la machine ciseau
    {
        gagnantARetourner = 'M';        //La machine gagne
    }

    return gagnantARetourner;   //Renvoie du resultat au programme appelant
}
