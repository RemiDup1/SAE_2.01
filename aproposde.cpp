#include "aproposde.h"
#include "ui_aproposde.h"

aproposde::aproposde(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aproposde)
{
    ui->setupUi(this);
    connect(ui->ok, SIGNAL(trigerred()), this, SLOT(close()));
}

aproposde::~aproposde()
{
    delete ui;
}


