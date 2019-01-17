#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
#include <vector>
#include <stdexcept>
#include <complex>
#include <QImage>
#include "fft.h"
#include <QtCore/qmath.h>
#define PI 3.1415926

using std::cout;
using std::endl;
using std::complex;
using std::vector;
using std::range_error;

template<typename T>
class Matrix
{
private:
    // point to the data
    T** _data;
    // number of row and column
    size_t _nRow, _nCol,_startR, _startC;
    // flag to indicate row-first or column-first
    int _t;
    void swap(Matrix<T>& mat);

public:
    // construct a r-row and c-column matrix with all init element
    Matrix(size_t r, size_t c, T init);
    // copy constructor
    Matrix(const Matrix<T>& mat);

    Matrix& operator=(Matrix<T> mat);
    Matrix<T> operator+(const Matrix<T>& mat);
    template<typename U>
    friend Matrix<U> operator+(U d, const Matrix<U>& mat);
    Matrix<T> operator-(const Matrix<T>& mat);
    template<typename U>
    friend Matrix<U> operator-(U d, const Matrix<U>& mat);
    template<typename U>
    friend Matrix<U> operator*(U d, const Matrix<U>& mat);
    Matrix<T> operator/(T);
    template<typename U>
    friend Matrix<U> operator *(const Matrix<U>& ,const Matrix<U>& );
    bool checkRange(size_t r, size_t c) const;

    ~Matrix();
    // get element at r-row and c-column
    // return reference to make it modifiable
    T& operator()(size_t r, size_t c) const;
    // output the matrix
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& rhs);
    size_t getNRow() const;
    size_t getNCol() const;
    std::vector<T> getRow(size_t r) const;
    std::vector<T> getCol(size_t c) const;
    bool setRow(size_t r, const std::vector<T>& d);
    bool setCol(size_t c, const std::vector<T>& d);
    // transpose it in-place
    Matrix<T>& transpose();

    Matrix<int> fromQImage(const QImage& img, const char c);
    QImage toQImage(const Matrix<int>& gray);
    QImage toQImage(const Matrix<int>& r, const Matrix<int>& g, const Matrix<int>& b);
    Matrix<int> LogTransform(const Matrix<int>& ret, double c);
    Matrix<double> parseMatrix(QString txt,int &size);

    Matrix<std::complex<double> > fft2d (const Matrix<int>& m, size_t s, size_t l);
    Matrix<std::complex<double> > fft2d (const Matrix<double>& m, size_t s, size_t l);
    Matrix<std::complex<double> > fft2d (const Matrix<std::complex<double> >& data, size_t M, size_t N);
    Matrix<std::complex<double> > ifft2d (const Matrix<int>& m, size_t s, size_t l);
    Matrix<std::complex<double> > ifft2d (const Matrix<double>& m, size_t s, size_t l);
    Matrix<std::complex<double> > ifft2d (const Matrix<std::complex<double> >& data, size_t M, size_t N);

    size_t calc(size_t length);
    Matrix<T>& fftshift();
    void rowCyclicShift(int);
    void colCyclicShift(int);

    static Matrix<T> inverted(const Matrix<T> & mat, bool *isInverted);
    static void map(const Matrix<double> & mat, const T x, const T y, T *mx, T *my);



};

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, T init):
_nRow(r), _nCol(c), _t(0),_startC(0), _startR(0)
{
    // new _data
    _data = new T *[_nRow];
    // new _data[i] within loop
    for(int i=0; i<_nRow; i++)
       _data[i] = new T[_nCol];

    for(int i=0; i<_nRow; i++)
       for(int j=0; j<_nCol; j++)
           _data[i][j] = init;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& mat):
_nRow(mat._nRow), _nCol(mat._nCol), _t(mat._t), _startR(0), _startC(0)
{
    // new _data
    _data = new T *[_nRow];
    // new _data[i] within loop
    for(int i=0; i<_nRow; i++)
       _data[i] = new T[_nCol];

    for(int i=0; i<_nRow; i++)
       for(int j=0; j<_nCol; j++)
           _data[i][j] = mat(i,j);
}

template<typename T>
void Matrix<T>::swap(Matrix<T>& mat) {
    std::swap(_data, mat._data);
    std::swap(_nRow, mat._nRow);
    std::swap(_nCol, mat._nCol);
    std::swap(_t, mat._t);
    std::swap(_startR, mat._startR);
    std::swap(_startC, mat._startC);
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> mat)
{
    swap(mat);
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& mat)
{
    Matrix<T> ret(mat._nRow, mat._nCol, mat(0, 0));
    for(size_t i=0; i<_nRow; i++)
       for(size_t j=0; j<_nCol; j++)
           ret(i, j) = operator ()(i, j) + mat(i,j);
    return ret;
}

template<typename T>
Matrix<T> operator+(T d, const Matrix<T>& mat)
{
    Matrix<T> ret(mat._nRow, mat._nCol, mat(0, 0));
    for(size_t i=0; i<mat._nRow; i++)
       for(size_t j=0; j<mat._nCol; j++)
           ret(i, j) = mat(i, j) + d;
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& mat)
{
    Matrix<T> ret(mat._nRow, mat._nCol, mat(0, 0));
    for(size_t i=0; i<_nRow; i++)
       for(size_t j=0; j<_nCol; j++)
           ret(i, j) = operator ()(i, j) - mat(i,j);
    return ret;
}

template<typename T>
Matrix<T> operator-(T d, const Matrix<T>& mat)
{
    Matrix<T> ret(mat._nRow, mat._nCol, mat(0, 0));
    for(size_t i=0; i<mat._nRow; i++)
       for(size_t j=0; j<mat._nCol; j++)
           ret(i, j) = d - mat(i, j);
    return ret;
}

template<typename T>
Matrix<T> operator*(T d, const Matrix<T>& mat)
{
    Matrix<T> ret(mat._nRow, mat._nCol, mat(0, 0));
    for(size_t i=0; i<mat._nRow; i++)
       for(size_t j=0; j<mat._nCol; j++)
           ret(i, j) = mat(i, j) * d;
    return ret;
}

template<typename U>
Matrix<U> operator *(const Matrix<U>& mat,const Matrix<U>&mar){
    double s=0;
    Matrix<U> ret(mat.getNRow(),mar.getNCol(),mat(0,0));
    for(int i=0;i<mat.getNRow();i++){
        for(int m=0;m<mar.getNCol();m++){
            for(int j=0;j<mat.getNCol();j++){
                s=s+mat(i,j)*mar(j,m);
            }
            ret(i,m)=s;
            s=0;
        }
    }
    return ret;
}
template<typename T>
Matrix<T> Matrix<T>::operator/(T d)
{
    Matrix<T> ret(_nRow, _nCol, operator ()(0, 0));
    for(size_t i=0; i<_nRow; i++)
       for(size_t j=0; j<_nCol; j++)
           ret(i, j) = operator ()(i, j)/d;
    return ret;
}

template<typename T>
size_t Matrix<T>::getNRow() const
{
    // return the number of row
    return _nRow;
}

template<typename T>
size_t Matrix<T>::getNCol() const
{
    return _nCol;
}

template<typename T>
bool Matrix<T>::checkRange(size_t r, size_t c) const
{
    // check if r-row and c-column is out of range
    if(r>_nRow || c>_nCol || r<0 || c<0)
    {
        /*std::range_error e("out of range");
        throw e;*/
        return false;
    }
    return true;
}

template<typename T>
T& Matrix<T>::operator()(size_t r, size_t c) const
{
    // get element in (r,c)
    // remember check first
    // different of _t has different order
    if(checkRange(r, c))
    {
        if(_t == 0)
            return _data[(r+_startR)%_nRow][(c+_startC)%_nCol];
        else
            return _data[(c+_startC)%_nCol][(r+_startR)%_nRow];
    }
}

template<typename T>
std::vector<T> Matrix<T>::getRow(size_t r) const
{
    vector<T> d(_nCol);
    if(checkRange(r, _nCol))
    {
        for(int j=0; j<_nCol; j++)
            d.at(j) = operator ()(r, j);
    }
    return d;
    // get all element in r-row and push it back in a vector
    // remember check range first
}

template<typename T>
std::vector<T> Matrix<T>::getCol(size_t c) const
{
    // get all element in c-column and push it back in a vector
    // remember check range first
    vector<T> d(_nRow);
    if(checkRange(_nRow, c))
    {
        for(int i=0; i<_nCol; i++)
            d.at(i) = operator ()(i, c);
    }
    return d;
}

template<typename T>
bool Matrix<T>::setRow(size_t r, const std::vector<T>& d)
{
    // set the element of the r-row
    // remember check range first
    if(checkRange(r, _nCol))
    {
        for(int j=0; j<_nRow; j++)
            operator ()(r, j) = d.at(j);
    }
}

template<typename T>
bool Matrix<T>::setCol(size_t c, const std::vector<T>& d)
{
    // set the element of the c-column
    // remember check range first
    if(checkRange(_nRow, c))
    {
        for(int i=0; i<_nCol; i++)
             operator ()(i, c) = d.at(i);
    }
}

template<typename T>
Matrix<T>::~Matrix()
{
    // delete _data[i] first
    for(int i=0; i<_nRow; i++)
        delete[] _data[i];
    // then delete _data
    delete[] _data;
    // note the value of _t
    _t = 0;
}

template<typename T>
Matrix<T>& Matrix<T>::transpose()
{
    // change _t
    if(_t == 0)
        _t = 1;
    else
        _t = 0;
    // swap _nRow and _nCol
    size_t temp = 0;
    temp = _nRow;
    _nRow = _nCol;
    _nCol = temp;
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& rhs)
{
    for(size_t i=0; i<rhs._nRow; ++i) {
        for(size_t j=0; j<rhs._nCol; ++j) {
            out << rhs(i,j) << "\t";
        }
        out << endl;
    }
    return out;
}

template<typename T>
Matrix<int> Matrix<T>::fromQImage(const QImage& img, const char c)
{
    QImage ret(img);
    int w = ret.width();
    int h = ret.height();
    Matrix<int> rgb(w, h, 0);
    if(c == 'r'){
        for(int i= 0; i<w; i++)
        {
            for(int j = 0; j<h; j++)
            {
                rgb(i, j) = qRed(ret.pixel(i, j));
            }
        }
    }
    else if(c == 'g'){
        for(int i= 0; i<w; i++)
        {
            for(int j = 0; j<h; j++)
            {
                rgb(i, j) = qGreen(ret.pixel(i, j));
            }
        }
    }
    else if(c == 'b'){
        for(int i= 0; i<w; i++)
        {
            for(int j = 0; j<h; j++)
            {
                rgb(i, j) = qBlue(ret.pixel(i, j));
            }
        }
    }
    else if(c == 'G'){
        for(int i= 0; i<w; i++)
        {
            for(int j = 0; j<h; j++)
            {
                rgb(i, j) = qGray(ret.pixel(i, j));
            }
        }
    }
    return rgb;
}

template<typename T>
QImage Matrix<T>::toQImage(const Matrix<int>& gray)
{
    int w = gray.getNRow();
    int h = gray.getNCol();
    QImage ret = QImage(w, h, QImage::Format_RGB32);
    for(int i= 0; i<w; i++)
    {
        for(int j = 0; j<h; j++)
        {
            ret.setPixel(i, j, qRgb(gray(i, j), gray(i, j), gray(i, j)));
        }
    }
    return ret;
}

template<typename T>
QImage Matrix<T>::toQImage(const Matrix<int>& r, const Matrix<int>& g, const Matrix<int>& b)
{
    int w = r.getNRow();
    int h = r.getNCol();
    QImage ret = QImage(w, h, QImage::Format_RGB32);
    for(int i= 0; i<w; i++)
    {
        for(int j = 0; j<h; j++)
        {
            ret.setPixel(i, j, qRgb(r(i, j), g(i, j), b(i, j)));
        }
    }
    return ret;
}
template<typename T>
Matrix<int> Matrix<T>::LogTransform(const Matrix<int> &ret, double c){
    double temp;
    for(size_t i=0; i<ret._nRow; i++)
       for(size_t j=0; j<ret._nCol; j++)
       {
           temp=ret(i,j)/255.0;
           temp = c*std::log(temp+1)*255;
           ret(i,j)=std::round(temp);
           if (ret(i,j)>255) ret(i,j)=255;
           if (ret(i,j)<0) ret(i,j)=0;
       }
    return ret;
}
template<typename T>
Matrix<double> Matrix<T>::parseMatrix(QString txt, int &size){
    QStringList matrix = txt.replace("\n","").trimmed().split(QRegularExpression("[,;]"));
    size = std::sqrt(matrix.size());
    Matrix<double> ret(size,size,0);
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            QString data=matrix[i*size+j];
            bool ok;
            double d=data.trimmed().toDouble(&ok);
            if(ok)
                ret(i,j)=d;
        }
    return ret;
}
template<typename T>
Matrix<T>& Matrix<T>::fftshift()
{
    rowCyclicShift(_nRow/2);
    colCyclicShift(_nCol/2);
    return *this;
}

template<typename T>
void Matrix<T>::rowCyclicShift(int r){
    _startR-=(r%_nRow);
    if(_startR<0) _startR+=_nRow;
}

template<typename T>
void Matrix<T>::colCyclicShift(int c){
    _startC-=(c%_nCol);
    if(_startC<0) _startC+=_nCol;
}
template<typename T>
size_t Matrix<T>::calc(size_t length) {
  // check if length is power of 2
  // if it is, just return length
  // if not, get the correct N and return
    if((length & (length - 1)) == 0) return length;
    else
    {
        size_t temp = length;
        while(length)
        {
            length = (length>>1);
            temp = length|temp;
        }
        return temp;
    }
}

template<typename T>
Matrix<complex<double> >
Matrix<T>::fft2d (const Matrix<int>& m, size_t s, size_t l) {
    Matrix<complex<double> > d(s, l, 0);
    for(int i = 0;i < s;i++)
        for(int j = 0;j < l;j++)
            d(i, j) = m(i, j);
    return fft2d(d, s, l);
}

template<typename T>
Matrix<complex<double> >
Matrix<T>::fft2d (const Matrix<double>& m, size_t s, size_t l) {
    Matrix<complex<double> > d(s, l, 0);
    for(int i = 0;i < s;i++)
        for(int j = 0;j < l;j++)
            d(i, j) = m(i, j);
    return fft2d(d, s, l);
}

template<typename T>
Matrix<complex<double> >
Matrix<T>::fft2d (const Matrix<complex<double> >& data, size_t M, size_t N) {
    M = calc(data.getNRow());
    N = calc(data.getNCol());
    if((M & (M - 1)) != 0 | (N & (N - 1)) != 0) {
        cout<<"error M or N"<<endl;
        return data;
    }
    Matrix<complex<double> > tempx(M, N, complex<double>(0, 0)),tempy(M, N, complex<double>(0, 0));

    for(int i = 0; i < N; i++)
    {
        tempx.setRow(i, fft(data.getRow(i)));
    }                                        //对X方向作FFT
    for(int i = 0; i < M; i++)
    {
        tempy.setCol(i, fft(tempx.getCol(i)));
    }                                        //对Y方向做傅里叶变换
    return tempy;
}

template<typename T>
Matrix<complex<double> >
Matrix<T>::ifft2d (const Matrix<complex<double> >& data, size_t M, size_t N) {
    M = calc(data.getNRow());
    N = calc(data.getNCol());
    if((M & (M - 1)) != 0 | (N & (N - 1)) != 0) {
        cout<<"error M or N"<<endl;
        return data;
    }
    Matrix<complex<double> > tempx(M, N, complex<double>(0, 0)),tempy(M, N, complex<double>(0, 0));

    for(int i = 0; i < N; i++)
    {
        tempx.setRow(i, ifft(data.getRow(i),M));
    }
    for(int i = 0; i < M; i++)
    {
        tempy.setCol(i, ifft(tempx.getCol(i),N));
    }
    return tempy;
}

template<typename T>
Matrix<complex<double> >
Matrix<T>::ifft2d (const Matrix<int>& m, size_t s, size_t l) {
    Matrix<complex<double> > d(s, l, 0);
    for(int i = 0;i < s;i++)
        for(int j = 0;j < l;j++)
            d(i, j) = m(i, j);
    return ifft2d(d, s, l);
}

template<typename T>
Matrix<complex<double> >
Matrix<T>::ifft2d (const Matrix<double>& m, size_t s, size_t l) {
    Matrix<complex<double> > d(s, l, 0);
    for(int i = 0;i < s;i++)
        for(int j = 0;j < l;j++)
            d(i, j) = m(i, j);
    return ifft2d(d, s, l);
}

template<typename T>
Matrix<T> Matrix<T>::inverted(const Matrix<T> & mat, bool *isInverted)
{
    //判断是否为3*3的矩阵
    if(mat.getNCol()!=3||mat.getNRow()!=3){ *isInverted=false;return Matrix(mat); }
    //计算mat的行列式
    T determinant=mat(0,0)*mat(1,1)*mat(2,2)+mat(0,1)*mat(1,2)*mat(2,0)+mat(0,2)*mat(1,0)*mat(2,1)
            -mat(0,2)*mat(1,1)*mat(2,0)-mat(0,1)*mat(1,0)*mat(2,2)-mat(0,0)*mat(1,2)*mat(2,1);
    //行列式为0则不可逆
    if(determinant==0){*isInverted=false;return Matrix(mat);}
    //计算逆矩阵
    *isInverted=true;
    Matrix<T> inmat(3, 3, 0);
    inmat(0,0)=    (mat(1,1)*mat(2,2)-mat(1,2)*mat(2,0))/determinant;
    inmat(1,0)= -1*(mat(1,0)*mat(2,2)-mat(1,2)*mat(2,0))/determinant;
    inmat(2,0)=    (mat(1,0)*mat(2,1)-mat(1,1)*mat(2,0))/determinant;
    inmat(0,1)= -1*(mat(0,1)*mat(2,2)-mat(0,2)*mat(2,1))/determinant;
    inmat(1,1)=    (mat(0,0)*mat(2,2)-mat(0,2)*mat(2,0))/determinant;
    inmat(2,1)= -1*(mat(0,0)*mat(2,1)-mat(0,1)*mat(2,0))/determinant;
    inmat(0,2)=    (mat(0,1)*mat(1,2)-mat(0,2)*mat(1,1))/determinant;
    inmat(1,2)= -1*(mat(0,0)*mat(1,2)-mat(0,2)*mat(1,0))/determinant;
    inmat(2,2)=    (mat(0,0)*mat(1,1)-mat(0,1)*mat(1,0))/determinant;
    return inmat;//返回逆矩阵
}
//3*3矩阵的映射
template<typename T>
void Matrix<T>::map(const Matrix<double> & mat, const T x, const T y, T *mx, T *my)
{
    *mx=mat(0,0)*x+mat(1,0)*y+mat(2,0);
    *my=mat(0,1)*x+mat(1,1)*y+mat(2,1);
}

#endif // MATRIX_H
