#include "parametres.h"
#include "ui_parametres.h"

Parametres::Parametres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametres)
{
    ui->setupUi(this);
    connect(ui->buttonValider, SIGNAL(accepted()), this, SLOT(ok()));
}

Parametres::~Parametres()
{
    delete ui;
}

void Parametres::ok()
{
    nom = ui->champNom->text();
    scoremax = ui->champScore->value();
    tempsmax = ui->champTemps->value();
}
