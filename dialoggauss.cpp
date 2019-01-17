#include "dialoggauss.h"
#include "ui_dialoggauss.h"
#include <QDebug>
DialogGauss::DialogGauss(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGauss)
{
    ui->setupUi(this);
}

DialogGauss::~DialogGauss()
{
    delete ui;
}
void DialogGauss::accept(){
    qDebug()<<"Gauss Filter accept"<<endl;
    bool ok1,ok2;
    int size=ui->lineEdit->text().toInt(&ok1);
    double sigma=ui->lineEdit_2->text().toDouble(&ok2);
    emit confirmed(size,sigma);
    close();
}
