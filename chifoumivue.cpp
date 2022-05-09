#include "chifoumivue.h"
#include "ui_chifoumivue.h"

chifoumiVue::chifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chifoumiVue)
{
    ui->setupUi(this);
}

chifoumiVue::~chifoumiVue()
{
    delete ui;
}

