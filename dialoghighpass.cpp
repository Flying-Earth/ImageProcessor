#include "dialoghighpass.h"
#include "ui_dialoghighpass.h"

DialogHighpass::DialogHighpass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHighpass)
{
    ui->setupUi(this);
}

DialogHighpass::~DialogHighpass()
{
    delete ui;
}
void DialogHighpass::accept(){
    bool ok;
    int radius=ui->lineEdit->text().toInt(&ok);
    if(ok)
        emit confirmed(radius);
    close();
}
