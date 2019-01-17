#include "dialoglog.h"
#include "ui_dialoglog.h"
#include <QDebug>

DialogLog::DialogLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLog)
{
    ui->setupUi(this);
}

DialogLog::~DialogLog()
{
    delete ui;
}
void DialogLog::accept(){
   bool ok;
   double c= ui->lineEdit->text().toDouble(&ok);
   if(ok){
       emit confirmed(c);
   }
   close();
}
