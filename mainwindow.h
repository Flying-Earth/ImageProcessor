#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include"mypismap.h"
#include "matrix.h"

#include "dialoglog.h"
#include "dialogcontrast.h"
#include "dialoglinear.h"
#include "dialogcrop.h"
#include "dialoggauss.h"
#include "dialogbilateral.h"
#include "dialogmid.h"
#include "dialogerode.h"
#include "dialogdilate.h"
#include "dialogaffine.h"
#include "dialoghighpass.h"
#include "dialoglowpass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_OpenButton_clicked();

    void on_SaveButton_clicked();

    void on_ResetButton_clicked();

    void on_PreviousButton_clicked();

    void on_NextButton_clicked();

private:
    Ui::MainWindow *ui;
    QFileDialog*fileDialog;//文件
    QStringList files;//字符串列表
    QGraphicsScene*scene;//创建一个可以供观看的场景
    Mypismap*pixmapItem;//自己定义的一个类，可用于控制窗口里面的物体
    QFileInfoList fileList;
    int currFileIdx;
    bool getDisplayedImage(QImage&)const;//这个函数是不可以修改东西的

    DialogLog *dialoglog;
    DialogContrast *dialogcontrast;
    DialogLinear *dialoglinear;
    DialogCrop *dialogcrop;
    DialogGauss *dialoggauss;
    DialogBilateral *dialogbilateral;
    DialogMid *dialogmid;
    DialogErode *dialogerode;
    DialogDilate *dialogdilate;
    DialogAffine *dialogaffine;
    DialogHighpass *dialoghighpass;
    DialogLowpass *dialoglowpass;

    void Open();
    void Save();
    void Reset();
    void Previous();
    void Next();
    void ShowImage(QImage);

private slots:
    void on_actionrgb2gray_triggered();
    void on_actionlogtransform_triggered();
    void on_actionopposite_triggered();
    void on_actioncontrastcontrol_triggered();
    void on_actionHistEq_triggered();
    void on_actionHistEqColor_triggered();
    void on_actionHistEqColor2_triggered();
    void on_actionLinear_triggered();
    void on_actionCrop_triggered();
    void on_actionGauss_triggered();
    void on_actionBilateral_triggered();
    void on_actionMid_triggered();
    void on_actionErode_triggered();
    void on_actionDilate_triggered();
    void on_actionFFT_triggered();
    void on_actionIFFT_triggered();
    void on_actionAffine_triggered();
    void on_actionHighpass_triggered();
    void on_actionLowpass_triggered();

    void on_DialogLog_confirmed(double);
    void on_DialogContrast_confirmed(double,double);
    void on_DialogLinear_confirmed(QString);
    void on_DialogCrop_confirmed(double,double);
    void on_DialogGauss_confirmed(int,double);
    void on_DialogBilateral_confirmed(int,double,double);
    void on_DialogMid_confirmed(int);
    void on_DialogErode_confirmed(int);
    void on_DialogDilate_confirmed(int);
    void on_DialogAffine_confirmed(const Matrix<double>&);
    void on_DialogHighpass_confirmed(int);
    void on_DialogLowpass_confirmed(int);
};

#endif // MAINWINDOW_H
