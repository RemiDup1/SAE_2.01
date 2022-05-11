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
    ui ->ChoixFigure->setEnabled(true);
    initCoups();
    initCoups();
    valJoueurScore = QString::number(scoreJoueur);
    ui ->ScoreVous->setText(valJoueurScore);
    valMachineScore = QString::number(scoreMachine);
    ui ->ScoreMachine->setText(valMachineScore);
}

void chifoumiVue::coupPierre()
{
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/pierre_115.png")));
    setCoupJoueur(2);
    deroulementPartie();
}

void chifoumiVue::coupCiseau()
{
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/ciseau_115.png")));
    setCoupJoueur(3);
    deroulementPartie();
}

void chifoumiVue::coupPapier()
{
    ui ->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/papier_115.png")));
    setCoupJoueur(1);
    qDebug () << "testT " << coupJoueur;
    deroulementPartie();
}



chifoumiVue::UnCoup chifoumiVue::getCoupJoueur()
{
    return coupJoueur;
}

chifoumiVue::UnCoup chifoumiVue::getCoupMachine()
{
    return coupMachine;
}

unsigned int chifoumiVue::getScoreJoueur()
{
    return scoreJoueur;
}

unsigned int chifoumiVue::getScoreMachine()
{
    return scoreMachine;
}

char chifoumiVue::determinerGagnant()
{
    qDebug() << "Debut determiner gagnant " << Qt::endl;
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';
    UnCoup joueur = getCoupJoueur();
    UnCoup machine = getCoupMachine();

    qDebug () << machine << " " << joueur ;
    if (machine == UnCoup::papier && joueur == UnCoup::ciseau) {
        gagnantARetourner = 'J';
        qDebug() << "Cas 1 " << Qt::endl;
    }
    if (machine == UnCoup::papier && joueur == UnCoup::pierre) {
        gagnantARetourner = 'M';
        qDebug() << "Cas 2 " << Qt::endl;
    }
    if (machine == UnCoup::pierre && joueur == UnCoup::ciseau) {
        gagnantARetourner = 'M';
        qDebug() << "Cas 3 " << Qt::endl;
    }
    if (machine == UnCoup::pierre && joueur == UnCoup::papier) {
        gagnantARetourner = 'J';
        qDebug() << "Cas 4 " << Qt::endl;
    }
    if (machine == UnCoup::ciseau && joueur == UnCoup::pierre) {
        gagnantARetourner = 'J';
        qDebug() << "Cas 5 " << Qt::endl;
    }
    if (machine == UnCoup::ciseau && joueur == UnCoup::papier) {
        gagnantARetourner = 'M';
        qDebug() << "Cas 6 " << Qt::endl;
    }
    qDebug() << "Fin determiner gagnant " << Qt::endl;
    return gagnantARetourner;
}

//Fonction permettant de determiner le score de la machine aléatoirement
int randMinMax(int min, int max)
{
     /*pré-condition : min<max, Le nbre aléatoire est compris entre [min, max[*/
    return rand()%(max-min) + min;
}


void chifoumiVue::setCoupJoueur(int num)
{
    qDebug () << num << Qt::endl;
    if (num == 1)
    {
        qDebug () << "init papier";
        coupJoueur = UnCoup::papier;
    }
    if (num == 2)
    {
        coupJoueur = UnCoup::pierre;
    }
    if (num == 3)
    {
        coupJoueur = UnCoup::ciseau;
    }

}

//fonction permettant d'indiquer le coup de la machine et de determiner le gagnant
void chifoumiVue::setCoupMachine()
{
    int num;
    num = randMinMax(1,4);

    if (num == 1)
    {
        ui ->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/papier_115.png")));
        coupMachine = UnCoup::papier;
    }
    if (num == 2)
    {
        ui ->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/pierre_115.png")));
        coupMachine = UnCoup::pierre;
    }
    if (num == 3)
    {
        ui ->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/ciseau_115.png")));
        coupMachine = UnCoup::ciseau;
    }
}

void chifoumiVue::setScoreJoueur(unsigned int p_score)
{
    scoreJoueur = scoreJoueur + p_score;
    valJoueurScore = QString::number(scoreJoueur);
    ui ->ScoreVous->setText(valJoueurScore);

}

void chifoumiVue::setScoreMachine(unsigned int p_score)
{
    scoreMachine = scoreMachine + p_score;

    valMachineScore = QString::number(scoreMachine);
    ui ->ScoreMachine->setText(valMachineScore);
}

void chifoumiVue::majScores(char p_gagnant)
{
    if (p_gagnant == 'J')
    {
        qDebug() << "gagnant joueur " << Qt::endl;
        setScoreJoueur(1);

    }
    if (p_gagnant == 'M')
    {
        qDebug() << "gagnant machine " << Qt::endl;
        setScoreMachine(1);
    }
}

void chifoumiVue::initScores()
{
    scoreJoueur = 0;
    scoreMachine = 0;
}

void chifoumiVue::initCoups()
{
    coupJoueur = rien;
    coupMachine = rien;
}

void chifoumiVue::deroulementPartie()
{
    qDebug() << "debut deroulement " << Qt::endl;
    char p_gagnant;
    setCoupMachine();
    p_gagnant = determinerGagnant();

    majScores(p_gagnant);
    qDebug() << "fin deroulement " << Qt::endl;
}
