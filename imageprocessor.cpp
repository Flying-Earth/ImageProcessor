#include "imageprocessor.h"
#include<cmath>
#include <QtCore/qmath.h>
#include "matrix.h"
#include <QDebug>
imageprocessor::imageprocessor()
{

}
QImage imageprocessor::rgb2gray(const QImage &img)
{
    Matrix<int> ret(0,0,0);
    ret=ret.fromQImage(img,'G');
    return ret.toQImage(ret);
}
QImage imageprocessor::LogTransformation(const QImage &img, double c){
    Matrix<int> ret(0,0,0);
    ret=ret.fromQImage(img,'G');
    ret=ret.LogTransform(ret,c);
    return ret.toQImage(ret);
}
QImage imageprocessor::opposite(const QImage &img){
    Matrix<int> r(0,0,0),g(0,0,0),b(0,0,0);
    r=r.fromQImage(img,'r');
    g=g.fromQImage(img,'g');
    b=b.fromQImage(img,'b');
    r=255-r;
    g=255-g;
    b=255-b;
    return r.toQImage(r,g,b);
}
QImage imageprocessor::contrastcontrol(const QImage &img, double m, double e){
    Matrix<int> gray(0,0,0),ret(0,0,0);
    gray=gray.fromQImage(img,'G');
    ret=gray;
    for(int i=0;i<gray.getNRow();i++)
        for(int j=0;j<gray.getNCol();j++)
        {
            int res=255/(1+pow(m/gray(i,j),e));
            if(res>255) res=255;
            if(res<0) res=0;
            ret(i,j)=res;
        }
    return ret.toQImage(ret);
}
QImage imageprocessor::HistEq(const QImage &img){
    Matrix<int> gray(0,0,0);
    gray=gray.fromQImage(img,'G');
    int hist[256]={0};
    int map[256]={0};
    int w=gray.getNRow();
    int h=gray.getNCol();
    long N=w*h;
    double sum=0;
    for(int i=0;i<w;i++){
        for(int j=0;j<h;++j){
            hist[gray(i,j)]++;
        }
    }
    for(int i=0;i<256;++i){
        sum += hist[i];
        map[i]=round(sum/N*255);
    }

    for(int i=0;i<w;i++){
        for(int j=0;j<h;++j){
            gray(i,j)= map[gray(i,j)];
        }
    }
    return gray.toQImage(gray);
}
QImage imageprocessor::HistEqColor(const QImage &img){
    Matrix<int> r(0,0,0),g(0,0,0),b(0,0,0);
    r=r.fromQImage(img,'r');
    g=g.fromQImage(img,'g');
    b=b.fromQImage(img,'b');
    int histr[256]={0};
    int histg[256]={0};
    int histb[256]={0};
    int mapr[256]={0};
    int mapg[256]={0};
    int mapb[256]={0};
    int w=r.getNRow();
    int h=r.getNCol();
    long N=w*h;
    Matrix<int> ret(w,h,0);
    double sumr=0;
    double sumg=0;
    double sumb=0;
    for(int i=0;i<w;i++){
        for(int j=0;j<h;++j){
            histr[r(i,j)]++;
        }
    }
    for(int i=0;i<w;i++){
        for(int j=0;j<h;++j){
            histg[g(i,j)]++;
        }
    }
    for(int i=0;i<w;i++){
        for(int j=0;j<h;++j){
            histb[b(i,j)]++;
        }
    }
    for(int i=0;i<256;++i){
        sumr += histr[i];
        mapr[i]=round(sumr/N*255);
    }
    for(int i=0;i<256;++i){
        sumg += histg[i];
        mapg[i]=round(sumg/N*255);
    }
    for(int i=0;i<256;++i){
        sumb += histb[i];
        mapb[i]=round(sumb/N*255);
    }

    for(int i=0;i<w;i++){
        for(int j=0;j<h;++j){
            r(i,j) = mapr[r(i,j)];
            g(i,j) = mapg[g(i,j)];
            b(i,j) = mapb[b(i,j)];
        }
    }
    return ret.toQImage(r,g,b);
}
QImage imageprocessor::HistEqColor2(const QImage &img){
    Matrix<int> r(0,0,0),g(0,0,0),b(0,0,0);
    r=r.fromQImage(img,'r');
    g=g.fromQImage(img,'g');
    b=b.fromQImage(img,'b');
    int w = r.getNRow();
    int h = r.getNCol();
    long N = w*h;
    Matrix<int> ret(w,h,0);
    HSI* Hsi = new HSI[N];
    for(int i=0; i<w; i++)
        for(int j=0; j<h; j++)
        {
            Hsi[i*h + j] = HSI();
            rgb2hsi(r(i,j),g(i,j),b(i,j), Hsi[i*h + j]);
        }

    int hist[256] = {0}, map[256] = {0};
    for(int i=0; i<N; i++)
        hist[int(Hsi[i].i*255)]++;

    cumulateHist(hist, map, N);

    for(int i=0; i<N; i++)
        Hsi[i].i = map[int(Hsi[i].i*255)]/255.0;

    for(int i= 0; i<w; i++)
    {
        for(int j = 0; j<h; j++)
        {
            int R,G,B;
            hsi2rgb(R,G,B, Hsi[i*h+j]);
            r(i,j)=R;
            g(i,j)=G;
            b(i,j)=B;
        }
    }

    delete Hsi;
    return ret.toQImage(r,g,b);
}
void imageprocessor::cumulateHist(int *hist, int *map, int N)
{
    double sum = 0;
    for(int i=0; i<256; i++)
    {
        sum += hist[i];
        map[i] = round(sum/N*255);
    }
}
void imageprocessor::rgb2hsi(int r,int g,int b, HSI &hsi)
{
    double var_R = r / 255.0;
    double var_G = g / 255.0;
    double var_B = b / 255.0;
    double H = 0, S = 0, L = 0;

    double var_Min = 255.0, var_Max = 0;
    if( var_R < var_G)
    {
        var_Min = var_R;
        var_Max = var_G;
        if( var_B < var_Min )
            var_Min = var_B;
        if( var_B > var_Max )
            var_Max = var_B;
    }
    else
    {
        var_Min = var_G;
        var_Max = var_R;
        if( var_B < var_Min )
            var_Min = var_B;
        if( var_B > var_Max )
            var_Max = var_B;
    }

    double del_Max = var_Max - var_Min;

    L = ( var_Max + var_Min )/ 2.0;

    if ( del_Max == 0 )
    {
        H = 0;
        S = 0;
    }
    else
    {
       if ( L < 0.5 ) S = del_Max / ( var_Max + var_Min );
       else           S = del_Max / ( 2.0 - var_Max - var_Min );

       double del_R = ( ( var_Max - var_R ) / 6.0 + ( del_Max / 2.0 ) ) / del_Max;
       double del_G = ( ( var_Max - var_G ) / 6.0 + ( del_Max / 2.0 ) ) / del_Max;
       double del_B = ( ( var_Max - var_B ) / 6.0 + ( del_Max / 2.0 ) ) / del_Max;

       if      ( var_R == var_Max ) H = del_B - del_G;
       else if ( var_G == var_Max ) H = 1.0 / 3.0 + del_R - del_B;
       else if ( var_B == var_Max ) H = 2.0 / 3.0 + del_G - del_R;

       if ( H < 0 ) H += 1.0;
       if ( H > 1 ) H -= 1.0;
    }
    hsi.h = H;
    hsi.s = S;
    hsi.i = L;
}
void imageprocessor::hsi2rgb(int &r,int &g,int &b, const HSI& hsi)
{

    double var_1 = 0, var_2 = 0;
    if ( hsi.s == 0 )
    {
       r = hsi.i * 255;
       g = hsi.i * 255;
       b = hsi.i * 255;
    }
    else
    {
       if ( hsi.i < 0.5 ) var_2 = hsi.i * ( 1 + hsi.s );
       else var_2 = ( hsi.i + hsi.s ) - ( hsi.s * hsi.i );

       var_1 = 2.0 * hsi.i - var_2;

       r = 255.0 * Hue_2_RGB( var_1, var_2, hsi.h + ( 1.0 / 3.0 ) );
       g = 255.0 * Hue_2_RGB( var_1, var_2, hsi.h );
       b = 255.0 * Hue_2_RGB( var_1, var_2, hsi.h - ( 1.0 / 3.0 ) );
    }

}
double imageprocessor::Hue_2_RGB(double v1, double v2, double vH)
{
   if ( vH < 0 ) vH += 1;
   if ( vH > 1 ) vH -= 1;
   if ( ( 6.0 * vH ) < 1 ) return v1 + ( v2 - v1 ) * 6.0 * vH;
   if ( ( 2.0 * vH ) < 1 ) return v2;
   if ( ( 3.0 * vH ) < 2 ) return v1 + ( v2 - v1 ) * ( ( 2.0 / 3.0 ) - vH ) * 6.0;
   return v1;
}

QImage imageprocessor::LinearFilter(const QImage &img, Matrix<double> &matrix){
    if(matrix.getNRow()%2==0)
        return img;
    MatrixNormalization(matrix);
    Matrix<int> r(0,0,0),g(0,0,0),b(0,0,0);
    r=r.fromQImage(img,'r');
    g=g.fromQImage(img,'g');
    b=b.fromQImage(img,'b');
    int w=r.getNRow(),h=r.getNCol();
    Matrix<int> R(w,h,0),G(w,h,0),B(w,h,0);
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            R(i,j)=CalculateFilter(r,matrix,i,j);
            G(i,j)=CalculateFilter(g,matrix,i,j);
            B(i,j)=CalculateFilter(b,matrix,i,j);
        }
    return R.toQImage(R,G,B);
}
int imageprocessor::CalculateFilter(const Matrix<int> &patch, const Matrix<double> &matrix, int _i, int _j){
    int size=matrix.getNRow();
    double sum=0;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            if(patch.checkRange(_i-size/2+i,_j-size/2+j))
                sum+=patch(_i-size/2+i,_j-size/2+j)*matrix(i,j);
            else
                sum+=0;
        }
    return int(sum);
}
void imageprocessor::MatrixNormalization(Matrix<double> &matrix){
    int size=matrix.getNRow();
    double sum=0;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            sum+=matrix(i,j);
        }
    if(sum!=0)
        matrix=matrix/sum;
}

QImage imageprocessor::Crop(const QImage &img, double w, double h){
    Matrix<int> r(0,0,0),g(0,0,0),b(0,0,0);
    r=r.fromQImage(img,'r');
    g=g.fromQImage(img,'g');
    b=b.fromQImage(img,'b');
    int W=img.width(),H=img.height();
    Matrix<int> R(W-w+1,H-h+1,0),G(W-w+1,H-h+1,0),B(W-w+1,H-h+1,0);
    for(int i=0;i<W-w+1;i++)
        for(int j=0;j<H-h+1;j++)
        {
            R(i,j)=r(i+w/2,j+h/2);
            G(i,j)=g(i+w/2,j+h/2);
            B(i,j)=b(i+w/2,j+h/2);
        }
    return R.toQImage(R,G,B);
}
QImage imageprocessor::Gauss(const QImage &img, int size, double sigma){
    if(size%2==0)
        return img;
    Matrix<double> gauss(size,size,0);
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            int deltaX=abs(i-size/2);
            int deltaY=abs(j-size/2);
            gauss(i,j)=exp((-deltaX*deltaX-deltaY*deltaY)/(2*sigma*sigma));
        }
    }
    return LinearFilter(img,gauss);
}
QImage imageprocessor::Bilateral(const QImage &img, int size, double sigmaColor, double sigmaSpace){
    if(size%2==0)
        return img;
    Matrix<double> space(size,size,0),matrix(size,size,0);
    std::vector<double> color;
    for(int i=0;i<256;++i)
        color.push_back(exp((-i*i)/(2*sigmaColor*sigmaColor)));
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            int deltaX=abs(i-size/2);
            int deltaY=abs(j-size/2);
            space(i,j)=exp((-deltaX*deltaX-deltaY*deltaY)/(2*sigmaSpace*sigmaSpace));
        }
    int width=img.width();
    int height=img.height();
    Matrix<int> ret(0,0,0);
    ret=ret.fromQImage(img,'G');
    for(int i=size/2;i<width-size/2;i++)
    {
        for(int j=size/2;j<height-size/2;j++)
        {
            for(int s=0;s<size;s++)
                for(int t=0;t<size;t++)
                {
                    int delta=abs(ret(s+i-size/2,t+j-size/2)-ret(i,j));
                    matrix(s,t)=color[delta]*space(s,t);
                }
            MatrixNormalization(matrix);
            double sum=0;
            for(int s=0;s<size;s++)
                for(int t=0;t<size;t++)
                {
                    sum+=matrix(s,t)*ret(s+i-size/2,t+j-size/2);
                }
            int y=(int)sum;
            if(y>255) y=255;
            ret(i,j)=y;
        }
    }
    QImage croped=Crop(ret.toQImage(ret),size,size);
    return croped;
}
QImage imageprocessor::Mid(const QImage &img, int size){
    if(size%2==0)
        return img;
    Matrix<int> r(0,0,0),g(0,0,0),b(0,0,0);
    r=r.fromQImage(img,'r');
    g=g.fromQImage(img,'g');
    b=b.fromQImage(img,'b');
    int w=img.width(),h=img.height();
    Matrix<int> R(w,h,0),G(w,h,0),B(w,h,0);
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            R(i,j)=SortFilter(r,size,i,j,2);
            G(i,j)=SortFilter(g,size,i,j,2);
            B(i,j)=SortFilter(b,size,i,j,2);
        }
    return r.toQImage(R,G,B);
}
int imageprocessor::SortFilter(const Matrix<int> &patch, int size, int _i, int _j, const int c){
    vector<int> temp;
    for(int i=_i-size/2;i<=_i+size/2;i++)
        for(int j=_j-size/2;j<=_j+size/2;j++)
        {
            if(patch.checkRange(i,j))
                temp.push_back(patch(i,j));
            else
                temp.push_back(0);
        }
    qSort(temp.begin(),temp.end());
    switch(c){
    case 1: return temp.front(); break;
    case 2: return temp.at(size*size/2);break;
    case 3: return temp.back();break;
    }
}

QImage imageprocessor::Erode(const QImage &img, int size){
    if(size%2==0)
        return img;
    Matrix<int> r(0,0,0),g(0,0,0),b(0,0,0);
    r=r.fromQImage(img,'r');
    g=g.fromQImage(img,'g');
    b=b.fromQImage(img,'b');
    int w=img.width(),h=img.height();
    Matrix<int> R(w,h,0),G(w,h,0),B(w,h,0);
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            R(i,j)=SortFilter(r,size,i,j,1);
            G(i,j)=SortFilter(g,size,i,j,1);
            B(i,j)=SortFilter(b,size,i,j,1);
        }
    return r.toQImage(R,G,B);
}
QImage imageprocessor::Dilate(const QImage &img, int size){
    if(size%2==0)
        return img;
    Matrix<int> r(0,0,0),g(0,0,0),b(0,0,0);
    r=r.fromQImage(img,'r');
    g=g.fromQImage(img,'g');
    b=b.fromQImage(img,'b');
    int w=img.width(),h=img.height();
    Matrix<int> R(w,h,0),G(w,h,0),B(w,h,0);
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            R(i,j)=SortFilter(r,size,i,j,3);
            G(i,j)=SortFilter(g,size,i,j,3);
            B(i,j)=SortFilter(b,size,i,j,3);
        }
    return r.toQImage(R,G,B);
}
QImage imageprocessor::fft(const QImage &img){
    Matrix<int> d(0,0,0);
    d=d.fromQImage(img, 'g');
    Matrix<complex<double> > m(d.getNRow(), d.getNCol(), 0);
    m = d.fft2d(d, d.getNRow(), d.getNCol());
    fftResult=m;
    int max = 1, min = 0;
    Matrix<int> ret(m.getNRow(), m.getNCol(), 0);
    for(int i= 0; i<m.getNRow(); i++)
    {
        for(int j = 0; j<m.getNCol(); j++)
        {
            ret(i, j) = qLn(1 + abs(m(i, j)));
            if(ret(i, j)>max) max = ret(i, j);
        }
    }
    for(int i= 0; i<m.getNRow(); i++)
    {
        for(int j = 0; j<m.getNCol(); j++)
        {
            ret(i, j) = 255 * (ret(i, j)-min ) / (max-min);
        }
    }
    ret.fftshift();
    return ret.toQImage(ret);
}
QImage imageprocessor::ifft(const QImage &img){
    int w=fftResult.getNCol(),h=fftResult.getNRow();
    Matrix<int> ret(w,h,0);
    fftResult=fftResult.ifft2d(fftResult,w,h);
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            ret(i,j)=fftResult(i,j).real();
        }
    return ret.toQImage(ret);
}
QImage imageprocessor::affine(const QImage &img, const Matrix<double> &mat){
    bool isInverted=true;
    Matrix<double> invertedMat=Matrix<double>::inverted(mat,&isInverted);
    if(!isInverted){ QImage ret(img);return ret; }
    //获取新图像的大小（将原图四个角映射到新图像坐标系中）
    int x_LeftUp=0,y_LeftUp=0,x_RightUp=0,y_RightUp=0,x_LeftDown=0,y_LeftDown=0,x_RightDown=0,y_RightDown=0;
    x_RightUp=img.width();y_LeftDown=img.height();
    x_RightDown=img.width();y_RightDown=img.height();
    //四个顶点的坐标
    int mx1,my1,mx2,my2,mx3,my3,mx4,my4;
    Matrix<int>::map(mat,x_LeftUp,y_LeftUp,&mx1,&my1);
    Matrix<int>::map(mat,x_RightUp,y_RightUp,&mx2,&my2);
    Matrix<int>::map(mat,x_LeftDown,y_LeftDown,&mx3,&my3);
    Matrix<int>::map(mat,x_RightDown,y_RightDown,&mx4,&my4);
    //获取新图片的范围
    int maxmx=getMax(mx1,mx2,mx3,mx4);
    int minmx=getMin(mx1,mx2,mx3,mx4);
    int maxmy=getMax(my1,my2,my3,my4);
    int minmy=getMin(my1,my2,my3,my4);
    //新图片的尺寸
    int h=maxmy-minmy;
    int w=maxmx-minmx;
    //构建新图像
    int dX=mx1-minmx;
    int dY=my1-minmy;
    QImage ret(w,h,QImage::Format_RGB32);
    for(int i=-dX;i<ret.width()-dX;i++)
    {
        for(int j=-dY;j<ret.height()-dY;j++)
        {
            double x,y;//(x,y)为原图像坐标
            Matrix<double>::map(invertedMat,i,j,&x,&y);
            if(x>=0&&x<img.width()-1&&y>=0&&y<img.height()-1)
            {
                QRgb qRgb=bilinearInterpolation(x,y,img);
                ret.setPixel(i+dX,j+dY,qRgb);
            }
            else{ ret.setPixel(i+dX,j+dY,qRgb(0,0,0)); }
        }
    }
    return ret;
}
int imageprocessor::getMax(int n1,int n2,int n3,int n4)
{
    int max=n1;
    if(n2>max)max=n2;
    if(n3>max)max=n3;
    if(n4>max)max=n4;
    return max;
}
//求最小值
int imageprocessor::getMin(int n1,int n2,int n3,int n4)
{
    int min=n1;
    if(n2<min)min=n2;
    if(n3<min)min=n3;
    if(n4<min)min=n4;
    return min;
}
//双线性插值
QRgb imageprocessor::bilinearInterpolation(double x, double y, const QImage & img)
{
    int r=0,g=0,b=0;
    int x_LeftUp=(int)x,x_RightUp=(int)x+1,x_LeftDown=(int)x,  x_RightDown=(int)x+1;
    int y_LeftUp=(int)y,y_RightUp=(int)y,  y_LeftDown=(int)y+1,y_RightDown=(int)y+1;
    QRgb rgb_LeftUp=img.pixel(x_LeftUp,y_LeftUp);
    QRgb rgb_RightUp=img.pixel(x_RightUp,y_RightUp);
    QRgb rgb_LeftDown=img.pixel(x_LeftDown,y_LeftDown);
    QRgb rgb_RightDown=img.pixel(x_RightDown,y_RightDown);
    r=((1-x+x_LeftUp)*qRed(  rgb_LeftDown)+(x-x_LeftUp)*qRed(  rgb_RightDown))*(1-y+y_LeftUp)+
      ((1-x+x_LeftUp)*qRed(  rgb_LeftUp)+(x-x_LeftUp)*qRed(  rgb_RightUp))*(  y-y_LeftUp);
    g=((1-x+x_LeftUp)*qGreen(rgb_LeftDown)+(x-x_LeftUp)*qGreen(rgb_RightDown))*(1-y+y_LeftUp)+
      ((1-x+x_LeftUp)*qGreen(rgb_LeftUp)+(x-x_LeftUp)*qGreen(rgb_RightUp))*(  y-y_LeftUp);
    b=((1-x+x_LeftUp)*qBlue( rgb_LeftDown)+(x-x_LeftUp)*qBlue( rgb_RightDown))*(1-y+y_LeftUp)+
      ((1-x+x_LeftUp)*qBlue( rgb_LeftUp)+(x-x_LeftUp)*qBlue( rgb_RightUp))*(  y-y_LeftUp);
    return QRgb(qRgb(r,g,b));
}

QImage imageprocessor::Highpass(const QImage &img, int radius){
    Matrix<int> gray(0,0,0);
    gray=gray.fromQImage(img,'G');
    int w=gray.getNCol(),h=gray.getNRow();
    Matrix<complex<double> > mat(w,h,0),ret(w,h,0);
    mat=gray.fft2d(gray,w,h);
    mat.fftshift();
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            /*if((i-w/2)*(i-w/2)+(j-h/2)*(j-h/2)<radius*radius)
                mat(i,j)=0;*/                                    //理想高通
            mat(i,j)=mat(i,j)*(1-qExp(-((i-w/2)*(i-w/2)+(j-h/2)*(j-h/2))/(2*radius*radius)));//高斯高通
        }
    mat.fftshift();
    ret=mat.ifft2d(mat,w,h);
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            gray(i,j)=ret(i,j).real();
        }
    return gray.toQImage(gray);

}
QImage imageprocessor::Lowpass(const QImage &img, int radius){
    Matrix<int> gray(0,0,0);
    gray=gray.fromQImage(img,'G');
    int w=gray.getNCol(),h=gray.getNRow();
    Matrix<complex<double> > mat(w,h,0),ret(w,h,0);
    mat=gray.fft2d(gray,w,h);
    mat.fftshift();
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            /*if((i-w/2)*(i-w/2)+(j-h/2)*(j-h/2)>radius*radius)
                mat(i,j)=0;*/                                    //理想低通
            mat(i,j)=mat(i,j)*qExp(-((i-w/2)*(i-w/2)+(j-h/2)*(j-h/2))/(2*radius*radius));//高斯低通
        }
    mat.fftshift();
    ret=mat.ifft2d(mat,w,h);
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            gray(i,j)=ret(i,j).real();
        }
    return gray.toQImage(gray);
}
