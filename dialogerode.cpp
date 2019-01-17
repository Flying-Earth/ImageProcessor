#include "dialogerode.h"
#include "ui_dialogerode.h"

DialogErode::DialogErode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogErode)
{
    ui->setupUi(this);
}

DialogErode::~DialogErode()
{
    delete ui;
}
void DialogErode::accept(){
    bool ok;
    int size=ui->lineEdit->text().toInt(&ok);
    if(ok)
        emit confirmed(size);
    close();
}
