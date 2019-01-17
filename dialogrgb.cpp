#include "dialogrgb.h"
#include "ui_dialogrgb.h"

Dialogrgb::Dialogrgb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogrgb)
{
    ui->setupUi(this);
}

Dialogrgb::~Dialogrgb()
{
    delete ui;
}
