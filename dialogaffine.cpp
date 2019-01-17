#include "dialogaffine.h"
#include "ui_dialogaffine.h"

DialogAffine::DialogAffine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAffine)
{
    ui->setupUi(this);
}

DialogAffine::~DialogAffine()
{
    delete ui;
}
void DialogAffine::accept(){
    Matrix<double> ret(3,3,0);
    ret(0,0)=ui->lineEdit->text().toDouble();
    ret(0,1)=ui->lineEdit_2->text().toDouble();
    ret(0,2)=ui->lineEdit_3->text().toDouble();
    ret(1,0)=ui->lineEdit_4->text().toDouble();
    ret(1,1)=ui->lineEdit_5->text().toDouble();
    ret(1,2)=ui->lineEdit_6->text().toDouble();
    ret(2,0)=ui->lineEdit_7->text().toDouble();
    ret(2,1)=ui->lineEdit_8->text().toDouble();
    ret(2,2)=ui->lineEdit_9->text().toDouble();
    emit confirmed(ret);
    close();
}
