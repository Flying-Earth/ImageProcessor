#include "dialogmid.h"
#include "ui_dialogmid.h"

DialogMid::DialogMid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMid)
{
    ui->setupUi(this);
}

DialogMid::~DialogMid()
{
    delete ui;
}
void DialogMid::accept(){
    bool ok;
    int size=ui->lineEdit->text().toInt(&ok);
    if(ok)
        emit confirmed(size);
    close();
}
