#ifndef SECONNECTER_H
#define SECONNECTER_H
/*
Header du fichier concernant la connexion à l'application (V7)
Dernière modification : 07/06/2022
*/
#include <QDialog>


namespace Ui {
class Seconnecter;
}

class Seconnecter : public QDialog
{
    Q_OBJECT

public:
    explicit Seconnecter(QWidget *parent = nullptr);
    ~Seconnecter();

    QString utilisateur;
    QString motdepasse;

private:
    Ui::Seconnecter *ui;

private slots:
    void valider();
};

#endif // SECONNECTER_H
