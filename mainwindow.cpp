#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include"imageprocessor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileDialog(new QFileDialog(this)),
    dialoglog(new DialogLog(this)),
    dialogcontrast(new DialogContrast(this)),
    dialoglinear(new DialogLinear(this)),
    dialogcrop(new DialogCrop(this)),
    dialoggauss(new DialogGauss(this)),
    dialogbilateral(new DialogBilateral(this)),
    dialogmid(new DialogMid(this)),
    dialogerode(new DialogErode(this)),
    dialogdilate(new DialogDilate(this)),
    dialogaffine(new DialogAffine(this)),
    dialoghighpass(new DialogHighpass(this)),
    dialoglowpass(new DialogLowpass(this)),
    scene(NULL), pixmapItem(NULL)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileDialog;
    delete dialoglog;
    delete dialogcontrast;
    delete dialoglinear;
    delete dialogcrop;
    delete dialoggauss;
    delete dialogbilateral;
    delete dialogmid;
    delete dialogerode;
    delete dialogdilate;
    delete dialogaffine;
    delete dialoghighpass;
    delete dialoglowpass;
    delete pixmapItem;
    delete scene;
}

void MainWindow::ShowImage(QImage img){
    if(pixmapItem){
        delete pixmapItem;
        pixmapItem=NULL;
    }
    if(scene){
        delete scene;
        scene=NULL;
    }

    pixmapItem=new Mypismap();

    pixmapItem->setPixmap(QPixmap::fromImage(img));

    scene=new QGraphicsScene(this);
    scene->addItem(pixmapItem);

    ui->graphicsView->setScene(scene);
}

void MainWindow::on_OpenButton_clicked()
{
    Open();
}
void MainWindow::Open()
{
    fileDialog->setNameFilter("Image(*.bmp *.jpg *.png)");
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    if(fileDialog->exec()){
         QStringList files=fileDialog->selectedFiles();//返回文件的地址
         QDir dir=fileDialog->directory();//文件的目录赋给dir
         QStringList filters;
         filters<<"*.bmp"<<"*.jpg"<<"*.png";
         fileList=dir.entryInfoList(filters);//选择文件格式
         for(int i=0;i<fileList.size();++i){
             if(fileList[i].absoluteFilePath()==files[0]){
                 currFileIdx=i;
                 break;
             }
         }
         qDebug()<<files[0]<<"\t"<<currFileIdx;
         ShowImage(QImage(fileList[currFileIdx].absoluteFilePath()));
         QString a;
         a.replace("\n","");
         a.split(";");
    }
}
void MainWindow::on_SaveButton_clicked(){
    Save();
}
void MainWindow::Save(){
    QImage img;
    bool ok=getDisplayedImage(img);
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    if(fileDialog->exec()&&ok){
        QString savename=fileDialog->selectedFiles()[0];
        img.save(savename);
    }
}
void MainWindow::on_ResetButton_clicked()
{
    Reset();
}
void MainWindow::Reset()
{
    ShowImage(QImage(fileList[currFileIdx].absoluteFilePath()));
    pixmapItem->reset();
    QRectF rect= pixmapItem->boundingRect();
    scene->setSceneRect(0,0,rect.width(),rect.height());
    ui->graphicsView->fitInView(rect,Qt::KeepAspectRatio);
}

void MainWindow::on_PreviousButton_clicked()
{
    Previous();
}
void MainWindow::Previous()
{
    if(currFileIdx==0){
        currFileIdx=fileList.size();
    }
    ShowImage(QImage(fileList[--currFileIdx].absoluteFilePath()));
    Reset();
}

void MainWindow::on_NextButton_clicked()
{
    Next();
}
void MainWindow::Next()
{
    if(currFileIdx==fileList.size()-1){
        currFileIdx=-1;
    }
    ShowImage(QImage(fileList[++currFileIdx].absoluteFilePath()));
    Reset();
}

bool MainWindow::getDisplayedImage(QImage &img) const{
    QList<QGraphicsItem*> items= ui->graphicsView->scene()->items();
    if(items.size()==0) return false;
    QGraphicsPixmapItem* item=(QGraphicsPixmapItem*) items.at(0);
    img=item->pixmap().toImage();
    return true;
}

void MainWindow::on_actionrgb2gray_triggered(){
    QImage img;
    if(getDisplayedImage(img)){
        QImage res=imageprocessor::rgb2gray(img);
        ShowImage(res);
    }
}
void MainWindow::on_actionlogtransform_triggered(){
    dialoglog->exec();
}
void MainWindow::on_actionopposite_triggered(){
    QImage img;
    if(getDisplayedImage(img)){
        QImage res=imageprocessor::opposite(img);
        ShowImage(res);
    }
}
void MainWindow::on_actioncontrastcontrol_triggered(){
    dialogcontrast->exec();
}
void MainWindow::on_actionHistEq_triggered(){
    QImage img;
    bool ok = getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::HistEq(img));
}
void MainWindow::on_actionHistEqColor_triggered(){
    QImage img;
    bool ok = getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::HistEqColor(img));
}
void MainWindow::on_actionHistEqColor2_triggered(){
    QImage img;
    bool ok = getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::HistEqColor2(img));
}
void MainWindow::on_actionLinear_triggered(){
    dialoglinear->exec();
}
void MainWindow::on_actionCrop_triggered(){
    dialogcrop->exec();
}
void MainWindow::on_actionGauss_triggered(){
    dialoggauss->exec();
}
void MainWindow::on_actionBilateral_triggered(){
    dialogbilateral->exec();
}
void MainWindow::on_actionMid_triggered(){
    dialogmid->exec();
}
void MainWindow::on_actionErode_triggered(){
    dialogerode->exec();
}
void MainWindow::on_actionDilate_triggered(){
    dialogdilate->exec();
}
void MainWindow::on_actionFFT_triggered(){
    QImage img;
    bool ok = getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::fft(img));
}
void MainWindow::on_actionIFFT_triggered(){
    QImage img;
    bool ok = getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::ifft(img));
}
void MainWindow::on_actionAffine_triggered(){
    dialogaffine->exec();
}
void MainWindow::on_actionHighpass_triggered(){
    dialoghighpass->exec();
}
void MainWindow::on_actionLowpass_triggered(){
    dialoglowpass->exec();
}
/************************* dialogconfirm **********************************************/

void MainWindow::on_DialogLog_confirmed(double c){
    qDebug()<<"receive c:"<<c;
    QImage img;
    if(getDisplayedImage(img)){
        QImage res=imageprocessor::LogTransformation(img,c);
        ShowImage(res);
    }
}
void MainWindow::on_DialogContrast_confirmed(double m, double e)
{
    QImage img;
    if(getDisplayedImage(img)){
        QImage res=imageprocessor::contrastcontrol(img,m,e);
        ShowImage(res);
    }
}
void MainWindow::on_DialogLinear_confirmed(QString txt){
    qDebug()<<"receive txt:"<<txt;
    Matrix<double> ret(0,0,0);
    int size=0;
    ret = ret.parseMatrix(txt,size);
    QImage img;
    if(getDisplayedImage(img)){
        QImage res=imageprocessor::LinearFilter(img,ret);
        ShowImage(res);
    }
}
void MainWindow::on_DialogCrop_confirmed(double w, double h){
    qDebug()<<"receive w:"<<w;
    qDebug()<<"receive h:"<<h;
    QImage img;
    if(getDisplayedImage(img)){
        QImage res=imageprocessor::Crop(img,w,h);
        ShowImage(res);
    }
}
void MainWindow::on_DialogGauss_confirmed(int size, double sigma){
    qDebug()<<"receive size:"<<size;
    qDebug()<<"receive sigma:"<<sigma;
    QImage img;
    if(getDisplayedImage(img)){
        QImage res=imageprocessor::Gauss(img,size,sigma);
        ShowImage(res);
    }
}
void MainWindow::on_DialogBilateral_confirmed(int size, double sigmaColor, double sigmaSpace){
    QImage img;
    bool ok=getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::Bilateral(img,size,sigmaColor,sigmaSpace));
}
void MainWindow::on_DialogMid_confirmed(int size){
    QImage img;
    bool ok=getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::Mid(img,size));
}
void MainWindow::on_DialogErode_confirmed(int size){
    QImage img;
    bool ok=getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::Erode(img,size));
}
void MainWindow::on_DialogDilate_confirmed(int size){
    QImage img;
    bool ok=getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::Dilate(img,size));
}
void MainWindow::on_DialogAffine_confirmed(const Matrix<double> &mat){
    QImage img;
    bool ok=getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::affine(img,mat));
}
void MainWindow::on_DialogHighpass_confirmed(int radius){
    QImage img;
    bool ok=getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::Highpass(img,radius));
}
void MainWindow::on_DialogLowpass_confirmed(int radius){
    QImage img;
    bool ok=getDisplayedImage(img);
    if(ok)
        ShowImage(imageprocessor::Lowpass(img,radius));
}
