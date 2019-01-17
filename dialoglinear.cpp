#include "dialoglinear.h"
#include "ui_dialoglinear.h"
#include <QDebug>

DialogLinear::DialogLinear(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLinear)
{
    ui->setupUi(this);
}

DialogLinear::~DialogLinear()
{
    delete ui;
}
void DialogLinear::accept(){
    qDebug()<<"Linear Filter accept"<<endl;

    QString txt=ui->textEdit->toPlainText();
    emit confirmed(txt);
    close();
}
