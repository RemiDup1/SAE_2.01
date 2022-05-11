#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class chifoumiVue; }
QT_END_NAMESPACE

class presentation;
class chifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    chifoumiVue(QWidget *parent = nullptr);
    ~chifoumiVue();

private slots:
    void demarerPartie();
    void coupPierre();
    void coupCiseau();
    void coupPapier();

///* Attributs du Modèle
private:
    presentation *_laPresentation;
    Ui::chifoumiVue *ui;



};
#endif // CHIFOUMIVUE_H
