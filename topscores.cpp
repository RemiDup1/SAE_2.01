/*
Corps du fichier gérant les paramètres des meilleurs scores (V9)
Dernière modification : 07/06/2022
*/

#include "topscores.h"
#include "ui_topscores.h"
#include <QtSql>

TopScores::TopScores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopScores)
{
    ui->setupUi(this);
    connect(ui->boutonOk, SIGNAL(clicked()), this, SLOT(close()));
}

TopScores::~TopScores()
{
    delete ui;
}

void TopScores::requeteBDD()
{
    QSqlQuery requete;
    requete.exec("SELECT * FROM ScoresChifoumi ORDER BY ScoreJ DESC, ScoreM ASC");

    for (int i = 0; requete.next() && i < 10; i++) {

        QTableWidgetItem *horodatage = new QTableWidgetItem(requete.value(0).toString());
        QTableWidgetItem *nomJ = new QTableWidgetItem(requete.value(1).toString());
        QTableWidgetItem *scoreJ = new QTableWidgetItem(requete.value(2).toString());
        QTableWidgetItem *scoreM = new QTableWidgetItem(requete.value(3).toString());

        ui->tableMScores->insertRow(i);
        ui->tableMScores->setItem(i, 0, nomJ);
        ui->tableMScores->setItem(i, 1, scoreJ);
        ui->tableMScores->setItem(i, 2, scoreM);
        ui->tableMScores->setItem(i, 3, horodatage);
    }
}

