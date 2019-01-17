#include "dialogdilate.h"
#include "ui_dialogdilate.h"

DialogDilate::DialogDilate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDilate)
{
    ui->setupUi(this);
}

DialogDilate::~DialogDilate()
{
    delete ui;
}
void DialogDilate::accept(){
    bool ok;
    int size=ui->lineEdit->text().toInt(&ok);
    if(ok)
        emit confirmed(size);
    close();
}
