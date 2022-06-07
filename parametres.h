#ifndef PARAMETRES_H
#define PARAMETRES_H
/*
Header du fichier concernant les paramètres de l'application (V6)
Dernière modification : 07/06/2022
*/

#include <QDialog>

namespace Ui {
class Parametres;
}

class Parametres : public QDialog
{
    Q_OBJECT

public:
    explicit Parametres(QWidget *parent = nullptr);
    ~Parametres();

    QString nom;
    int scoremax;
    int tempsmax;

private:
    Ui::Parametres *ui;

private slots:
    void ok();
};

#endif // PARAMETRES_H
