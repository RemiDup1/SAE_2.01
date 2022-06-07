#ifndef TOPSCORES_H
#define TOPSCORES_H

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
