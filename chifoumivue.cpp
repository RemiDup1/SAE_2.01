/*
 * Programme du chifoumi
 * programmation de la V3/V4
 * Statut : V3 Terminée, V4 en cours
 * Date dernier modification : 24/05/2022
 * auteur(s) : Dupin Remi / Cattarossi Dartiguelongue Thomas / Errezarret Leho
 *
*/
#include "chifoumivue.h"
#include "ui_chifoumivue.h"
#include "presentation.h"
#include "modele.h"
#include <QDebug>
#include <QDialog>



chifoumiVue::chifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chifoumiVue)
{
    ui->setupUi(this);

    db = new Database(); // Lancement de la base de données
    db->openDataBase();
    db->restoreDataBase();

    connexion = new Seconnecter(); // Aller vers la page de connexion
    connexion->exec();

    ui->labelTempsImparti->setText(QString::number(LIMITE_TEMPS));
    ui->LabelNom->setText(nomJoueur);

    connect(ui ->action_Quitter, SIGNAL(triggered()), this, SLOT(close()));                 //Connexion avec l'option quitter dans l'onglet fichier
    connect(ui -> BoutNouvellePartie, SIGNAL(clicked()), this, SLOT(demarrerPartie()));     //Connexion du bouton nouvelle partie avec le slot qui demarre la partie
    connect(ui -> BoutPierre, SIGNAL(clicked()), this, SLOT(coupPierre()));                 //Connexion du bouton pierre avec le slot qui permet au joueur de jouer pierre
    connect(ui->BoutCiseaux, SIGNAL(clicked()), this, SLOT(coupCiseau()));                  //Connexion du bouton ciseau avec le slot qui permet au joueur de jouer ciseau
    connect(ui->BoutPapier, SIGNAL(clicked()), this, SLOT(coupPapier()));                   //Connexion du bouton papier avec le slot qui permet au joueur de jouer papier
    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(aProposDe()));           //Connexion avec l'option A Propos De dans l'onglet Aide
    connect(compteARebours, SIGNAL(timeout()), this, SLOT(decompte()));                     // Connexion entre le compte à rebours et le slot permettant le décompte
    connect(ui->actionParametrage, SIGNAL(triggered()), this, SLOT(parametrage()));          // Connexion entre l'action de paramétrage de la partie et le slot paramétrer
    connect(ui->BoutPause, SIGNAL(clicked()), this, SLOT(pause()));                         // Connexion entre le bouton de mise en pause de la partie et le slot permettant de le faire

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
    QString valScoreJ;
    valScoreJ = QString::number(scoreJ);
    ui->ScoreVous->setText(valScoreJ);
}

void chifoumiVue::afficherScoreMachine(unsigned int scoreM)
{
    QString valScoreM;
    valScoreM = QString::number(scoreM);
    ui->ScoreMachine->setText(valScoreM);
}

void chifoumiVue::afficherCoupJoueur(Modele::UnCoup coupJ)
{
    QString valCoupJ = afficherNomCoup(coupJ);
    if (valCoupJ == "rien")
    {
        ui->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/rien_115.png")));
    }
    if (valCoupJ == "pierre")
    {
        ui->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/pierre_115.png")));
    }
    if (valCoupJ == "papier")
    {
        ui->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/papier_115.png")));
    }
    if (valCoupJ == "ciseau")
    {
        ui->ImageChoixUtili->setPixmap(QPixmap(QString::fromUtf8(":/images/images/ciseau_115.png")));
    }
}

void chifoumiVue::afficherCoupMachine(Modele::UnCoup coupM)
{
    QString valCoupM = afficherNomCoup(coupM);
    if (valCoupM == "rien")
    {
        ui->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/rien_115.png")));
    }
    if (valCoupM == "pierre")
    {
        ui->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/pierre_115.png")));
    }
    if (valCoupM == "papier")
    {
        ui->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/papier_115.png")));
    }
    if (valCoupM == "ciseau")
    {
        ui->ImageChoixMachi->setPixmap(QPixmap(QString::fromUtf8(":/images/images/ciseau_115.png")));
    }
}

void chifoumiVue::majInterface(Presentation::UnEtatJeu e)
{
    switch (e)
    {
        case Presentation::etatInitial:
            ui -> actionParametrage ->setEnabled(true);
            ui -> ChoixFigure -> setEnabled(false);
            ui -> BoutPause -> setEnabled(false);
            break;
        case Presentation::partieEnCours:
            compteARebours->start();
            ui -> actionParametrage ->setEnabled(false);
            ui -> ChoixFigure -> setEnabled(true);
            ui -> BoutPause -> setEnabled(true);
            ui -> BoutNouvellePartie -> setEnabled(true);
            break;
        case Presentation::partieEnPause: // Si la partie est en pause :
            compteARebours->stop();
            ui -> BoutNouvellePartie -> setEnabled(false);
            ui -> ChoixFigure -> setEnabled(false);
            ui -> BoutPause -> setText("Reprendre");
        default:
            break;
        ui ->BoutNouvellePartie->setFocus();

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
    tempsRestant = getPresentation()->paramTemps; // Initialisation du compte à rebours
    setLimiteScore(getPresentation()->paramScore);
    ui->labelTempsImparti->setText(QString::number(tempsRestant));
    ui->labelTempsImparti->show();
    compteARebours->start(1000);

    getPresentation()->demarrerPartie();
}

void chifoumiVue::arreterPartie()
{
    getPresentation()->arreterPartie();

}

void chifoumiVue::coupPierre()
{
    getPresentation()->coupPierre();
}

void chifoumiVue::coupCiseau()
{
    getPresentation()->coupCiseau();
}

void chifoumiVue::coupPapier()
{
    getPresentation()->coupPapier();
}

void chifoumiVue::aProposDe()
{
    QString auteurs = "Auteurs :";
    QString listeAuteurs = "DUPIN Rémi \nERREZARRET Leho \nCATTAROSSI DARTIGUELONGUE Thomas";
    QMessageBox::information(this, auteurs, listeAuteurs);
}

void chifoumiVue::decompte()
{
    tempsRestant--;
    QString tps = QString::number(tempsRestant);
    ui->labelTempsImparti->setText(tps);
    compteARebours->start(1000);
    getPresentation()->tempsEcoule();
}

void chifoumiVue::pause()
{
    getPresentation()->pausePartie();
}

void chifoumiVue::parametrage()
{
    param = new Parametres();
    param->exec();

    getPresentation()->parametrer();
    QString tps = QString::number(tempsRestant);
    ui->labelTempsImparti->setText(QString::number(getPresentation()->paramTemps));
    ui->LabelNom->setText(nomJoueur);
    setLimiteScore(getPresentation()->paramScore);
}

void chifoumiVue::setLimiteScore(int scorePT)
{
    QString score = QString::number(scorePT);
    ui->labelLimiteScore->setText(score);
    ui->labelLimiteScore->show();
    ui->labelScoreMax->show();
}




