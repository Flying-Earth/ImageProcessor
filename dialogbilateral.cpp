#include "dialogbilateral.h"
#include "ui_dialogbilateral.h"

DialogBilateral::DialogBilateral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBilateral)
{
    ui->setupUi(this);
}

DialogBilateral::~DialogBilateral()
{
    delete ui;
}
void DialogBilateral::accept()
{
    bool ok;
   int size= ui->lineEdit->text().toDouble(&ok);//这里的ok判断这里是否有值输入。
   double sigmaColor= ui->lineEdit_2->text().toDouble(&ok);
   double sigmaSpace= ui->lineEdit_3->text().toDouble(&ok);
   if(ok){
       emit confirmed(size,sigmaColor,sigmaSpace);

   }
   close();
}
