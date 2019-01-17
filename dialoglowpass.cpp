#include "dialoglowpass.h"
#include "ui_dialoglowpass.h"

DialogLowpass::DialogLowpass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLowpass)
{
    ui->setupUi(this);
}

DialogLowpass::~DialogLowpass()
{
    delete ui;
}
void DialogLowpass::accept(){
    bool ok;
    int radius=ui->lineEdit->text().toInt(&ok);
    if(ok)
        emit confirmed(radius);
    close();
}
