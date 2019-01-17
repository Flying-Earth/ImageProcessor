#include "dialogcrop.h"
#include "ui_dialogcrop.h"

DialogCrop::DialogCrop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCrop)
{
    ui->setupUi(this);
}

DialogCrop::~DialogCrop()
{
    delete ui;
}
void DialogCrop::accept(){
    bool ok1,ok2;
    double w=ui->lineEdit->text().toDouble(&ok1);
    double h=ui->lineEdit_2->text().toDouble(&ok2);
    if(ok1&&ok2)
        emit confirmed(w,h);
    close();
}
