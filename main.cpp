#include "mainwindow.h"
#include <QApplication>
#include "matrix.h"

using std::cout;
using std::endl;
using std::vector;
using std::range_error;

void test_matrix();
void test_fft();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //test_matrix();
    //test_fft();
    return a.exec();
}

void test_fft()
{
    vector<double> a;
    a.push_back(4.);
    a.push_back(3.);
    a.push_back(144);
    a.push_back(6.);
    a.push_back(32.);
    a.push_back(8.);
    a.push_back(9.);
    a.push_back(255);
    for (size_t i = 0; i < a.size(); ++i) {
        cout << a.at(i) << "\t";
    }
    cout << endl;
    vector<complex<double> > r = fft(a, 8);
    for(size_t i=0; i<r.size(); ++i)
        cout << r.at(i) << "\t";
    cout << endl;
    vector<complex<double> > t = ifft(r, 8);
    for (size_t i = 0; i < t.size(); ++i) {
        cout << t.at(i) << "\t";
    }
    cout << endl;
    cout << endl;
}
void test_matrix()
{
    cout << "------------------------------------" << endl;
    cout << "test of constructor:" << endl;
    cout << "------------------------------------" << endl;
    Matrix<int> m(5,4,4);
    cout << "*******    m:\n" << m << endl;;
    Matrix<int> mC(m);
    cout << "*******    mC:\n" << mC << endl;
    Matrix<int> mE = m;
    cout << "*******    mE:\n" << mE << endl;
    cout << "------------------------------------" << endl;
    cout << "test of operator()" << endl;
    cout << "------------------------------------" << endl;
    mC(1,2) = 2;
    cout << "*******  mC:\n" << mC << endl;
    mE(2,0) = 7;
    cout << "*******  mE:\n" << mE << endl;
    cout << "*******  m:\n" << m << endl;
    cout << "------------------------------------" << endl;
    cout << "test of transpose()" << endl;
    cout << "------------------------------------" << endl;
    cout << "*******  transpose mE:\n" << mE.transpose() << endl;
    cout << "------------------------------------" << endl;
    cout << "test of get and set" << endl;
    cout << "------------------------------------" << endl;
    vector<int> vd = mE.getRow(0);
    cout << "get the first row of mE:" << endl;
    for(size_t i = 0; i<vd.size(); ++i)
        cout << vd.at(i) << "  **  ";
    cout << endl;
    cout << "set the last column of mC:" << endl;
    vd.at(1) = -3.3;
    mC.setCol(3, vd);
    cout << "*******  mC:\n" << mC << endl;
    cout << "------------------------------------" << endl;
    cout << "test of exception" << endl;
    cout << "------------------------------------" << endl;
    try {
        cout << mC(0,2) << endl;
        cout << mE(5,6) << endl;
    } catch (range_error e) {
        cout << e.what() << endl;
    }
    cout << "------------------------------------" << endl;
    cout << "test of operator+" << endl;
    cout << "------------------------------------" << endl;
    mC(3,1) = -10;
    cout << "*******  m+mC:\n" << m+mC << endl;
    cout << "*******  9+mC:\n" << 9+mC << endl;
    cout << "------------------------------------" << endl;
    cout << "test of operator-" << endl;
    cout << "------------------------------------" << endl;
    mC(3,2) = 4;
    cout << "*******  m-mC:\n" << m-mC << endl;
    cout << "*******  10-mC:\n" << 10-mC << endl;
    cout << "------------------------------------" << endl;
    cout << "test of operator*" << endl;
    cout << "------------------------------------" << endl;
    cout << "*******  mE*mC:\n" << mE*mC << endl;
    cout << "*******  10*mC:\n" << 10*mC << endl;
    cout << "------------------------------------" << endl;
    cout << "test of operator/" << endl;
    cout << "------------------------------------" << endl;
    cout << "*******  mC/2:\n" << mC/2 << endl;

}
