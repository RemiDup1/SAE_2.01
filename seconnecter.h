#ifndef SECONNECTER_H
#define SECONNECTER_H

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
