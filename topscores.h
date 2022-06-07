#ifndef TOPSCORES_H
#define TOPSCORES_H
/*
Header du fichier concernant l'affichage des meilleurs scores (V9)
Dernière modification : 07/06/2022
*/
#include <QDialog>

namespace Ui {
class TopScores;
}

class TopScores : public QDialog
{
    Q_OBJECT

public:
    explicit TopScores(QWidget *parent = nullptr);
    ~TopScores();
    void requeteBDD();

private:
    Ui::TopScores *ui;
};

#endif // TOPSCORES_H
