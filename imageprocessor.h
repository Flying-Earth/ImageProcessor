#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include<QImage>
#include<vector>
#include "matrix.h"
using namespace std;

struct HSI{
    double h;
    double s;
    double i;
};
static Matrix<complex<double> > fftResult(0,0,0);
class imageprocessor
{
public:
    imageprocessor();
    static QImage rgb2gray(const QImage&);
    static QImage LogTransformation(const QImage&, double);
    static QImage opposite(const QImage&);
    static QImage contrastcontrol(const QImage&, double m, double e);
    static QImage HistEq(const QImage&);
    static QImage HistEqColor(const QImage&);
    static QImage HistEqColor2(const QImage&);
    static QImage LinearFilter(const QImage&,  Matrix<double>&);
    static QImage Crop(const QImage&, double w, double h);
    static QImage Gauss(const QImage&,int size,double sigma);
    static QImage Bilateral(const QImage&,int size,double sigmaColor,double sigmaSpace);
    static QImage Mid(const QImage& img, int size);
    static QImage Erode(const QImage& img, int size);
    static QImage Dilate(const QImage& img, int size);
    static QImage fft(const QImage& img);
    static QImage ifft(const QImage& img);
    static QImage affine(const QImage& img,const Matrix<double> &mat);
    static QImage Highpass(const QImage& img, int radius);
    static QImage Lowpass(const QImage& img, int radius);

    static void cumulateHist(int *, int *, int);
    static void rgb2hsi(int r,int g,int b, HSI&);
    static void hsi2rgb(int &r,int &g,int &b, const HSI&);
    static double Hue_2_RGB(double ,double ,double );
    static int CalculateFilter(const Matrix<int>& patch, const Matrix<double>& matrix, int _i, int _j);
    static void MatrixNormalization(Matrix<double> &);
    static int SortFilter(const Matrix<int>& patch, int size, int _i, int _j,const int c);
    static int getMax(int n1,int n2,int n3,int n4);
    static int getMin(int n1,int n2,int n3,int n4);
    static QRgb bilinearInterpolation(double x, double y, const QImage & img);



};

#endif // IMAGEPROCESSOR_H
