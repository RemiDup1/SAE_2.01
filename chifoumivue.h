#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include <QDebug>
#include "modele.h"
#include "Presentation.h"
#include <QDialog>
#include <QMessageBox>


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


private slots:
    void demarrerPartie();
    void coupPierre();
    void coupCiseau();
    void coupPapier();
    void aProposDe();

///* Attributs du Modèle
private:
    Presentation *laPresentation;
    Ui::chifoumiVue *ui;



};
#endif // CHIFOUMIVUE_H
