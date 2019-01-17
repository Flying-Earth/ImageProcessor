#include "dialogcontrast.h"
#include "ui_dialogcontrast.h"
#include <QDebug>

DialogContrast::DialogContrast(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogContrast)
{
    ui->setupUi(this);
}

DialogContrast::~DialogContrast()
{
    delete ui;
}
void DialogContrast::accept(){
    bool ok;
    double m= ui->lineEdit->text().toDouble(&ok);
    double e= ui->lineEdit_2->text().toDouble(&ok);
    if(ok){
        emit confirmed(m,e);
    }
    close();
}
