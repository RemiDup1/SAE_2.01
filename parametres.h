#ifndef PARAMETRES_H
#define PARAMETRES_H

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

    QString *nom;
    int *scoremax;
    int *tempsmax;

private:
    Ui::Parametres *ui;

private slots:
    void ok();
};

#endif // PARAMETRES_H
