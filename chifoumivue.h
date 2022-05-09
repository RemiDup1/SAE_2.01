#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class chifoumiVue; }
QT_END_NAMESPACE

class chifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    chifoumiVue(QWidget *parent = nullptr);
    ~chifoumiVue();

private:
    Ui::chifoumiVue *ui;
};
#endif // CHIFOUMIVUE_H
