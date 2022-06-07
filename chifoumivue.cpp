/*
Corps du fichier concernant la vue de l'application
Dernière modification : 07/06/2022
*/

#include "chifoumivue.h"
#include "ui_chifoumivue.h"

#include <QDebug>
#include <QDialog>



chifoumiVue::chifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chifoumiVue)
{
    ui->setupUi(this);

    // Ajout + Création + Connexion à la base de données (V7)
    db = new Database();
    db->openDataBase();
    db->restoreDataBase();

    // Affichage de la fenêtre de connexion (V7)
    connexion = new Seconnecter();
    connexion->exec();

    // Affichage à l'écran des informations par défaut
    //ui->labelTempsImparti->setText(QString::number(getPresentation()->paramTemps));
    //ui->LabelNom->setText(nomJoueur);

    // CONNEXIONS DES BOUTONS / SLOTS

    // V2
    connect(ui->BoutNouvellePartie, SIGNAL(clicked()), this, SLOT(demarrerPartie())); // Connexion du bouton nouvelle partie avec le slot qui demarre la partie

    // V3
    connect(ui->action_Quitter, SIGNAL(triggered()), this, SLOT(close())); // Connexion avec l'option quitter dans l'onglet fichier

    connect(ui->BoutPierre, SIGNAL(clicked()), this, SLOT(coupPierre())); // Connexion du bouton pierre avec le slot qui permet au joueur de jouer pierre
    connect(ui->BoutCiseaux, SIGNAL(clicked()), this, SLOT(coupCiseau())); // Connexion du bouton ciseau avec le slot qui permet au joueur de jouer ciseau
    connect(ui->BoutPapier, SIGNAL(clicked()), this, SLOT(coupPapier())); // Connexion du bouton papier avec le slot qui permet au joueur de jouer papier

    // V3
    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(aProposDe())); // Connexion avec l'option A Propos De dans l'onglet Aide

    // V5
    connect(ui->BoutPause, SIGNAL(clicked()), this, SLOT(pause())); // Connexion entre le bouton de mise en pause de la partie et le slot permettant de le faire
    connect(compteARebours, SIGNAL(timeout()), this, SLOT(decompte())); // Connexion entre le compte à rebours et le slot permettant le décompte

    // V6
    connect(ui->actionParametrage, SIGNAL(triggered()), this, SLOT(parametrage())); // Connexion entre l'action de paramétrage de la partie et le slot paramétrer

    // V9
    connect(ui->actionMeilleurs_Scores, SIGNAL(triggered()), this, SLOT(topScores()));

}



chifoumiVue::~chifoumiVue()
{
    delete ui;
}

/*
 * Corps des procédures
*/

// Getter / Setter pour Presentation (V2)
void chifoumiVue::setPresentation(Presentation *p)
{laPresentation = p;}
Presentation *chifoumiVue::getPresentation()
{return laPresentation;}

// Affichage des Scores et des Coups du Joueur et de la Machine
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

// Mise à jour de l'interface (V2 / V5 / V6)
void chifoumiVue::majInterface(Presentation::UnEtatJeu e)
{
    switch (e)
    {
        case Presentation::etatInitial:
            ui -> ChoixFigure -> setEnabled(false);
            ui -> BoutPause -> setEnabled(false); // V5
            ui -> actionParametrage ->setEnabled(true); // V6
            break;
        case Presentation::partieEnCours:
            compteARebours->start();
            ui -> BoutNouvellePartie -> setEnabled(true);
            ui -> ChoixFigure -> setEnabled(true);
            ui -> BoutPause -> setEnabled(true); // V5
            ui -> BoutPause -> setText("Mettre sur Pause"); // V5
            ui -> actionParametrage ->setEnabled(false); // V6

            break;
        case Presentation::partieEnPause: // Si la partie est en pause :
            compteARebours->stop();
            ui -> BoutNouvellePartie -> setEnabled(false);
            ui -> ChoixFigure -> setEnabled(false);
            ui -> BoutPause -> setText("Reprendre"); // V5
        default:
            break;
        ui ->BoutNouvellePartie->setFocus();

    }
}

// Afficher le nom du coup (V2)
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

// Effectuer la limite de score (V4)
void chifoumiVue::setLimiteScore(int scorePT)
{
    QString score = QString::number(scorePT);
    ui->labelLimiteScore->setText(score);
    ui->labelLimiteScore->show();
    ui->labelScoreMax->show();
}

/*
 * Corps des slots
*/

// Démarrer / Arrêter partie (V2 / V5)
void chifoumiVue::demarrerPartie()
{
    // Initialisation du compte à rebours
    tempsRestant = getPresentation()->paramTemps;
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

// Slots des Coups (V2)
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

// Slot A Propos De (V3)
void chifoumiVue::aProposDe()
{
    QString auteurs = "Auteurs :";
    QString listeAuteurs = "DUPIN Rémi \nERREZARRET Leho \nCATTAROSSI DARTIGUELONGUE Thomas";
    QMessageBox::information(this, auteurs, listeAuteurs);
}

// Slots Compte à Rebours (V5)
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

// Slot Paramétrage (V6)
void chifoumiVue::parametrage()
{
    param = new Parametres();
    param->exec();

    // Actualisation des paramètres
    getPresentation()->parametrer();
    QString tps = QString::number(tempsRestant);
    ui->labelTempsImparti->setText(QString::number(getPresentation()->paramTemps));
    ui->LabelNom->setText(nomJoueur);
    setLimiteScore(getPresentation()->paramScore);
}

// Slot Meilleurs Scores (V9)
void chifoumiVue::topScores()
{
    scores = new TopScores();
    scores->hide();
    scores->requeteBDD();
    scores->show();
}




