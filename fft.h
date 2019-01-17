#ifndef FFT_H
#define FFT_H

#include <iostream>
#include <vector>
#include <complex>

#define PI 3.1415926

using std::cout;
using std::endl;
using std::complex;
using std::vector;
using std::range_error;

class FFT
{
public:
    static size_t calcN(size_t length);
    static std::complex<double> pow(std::complex<double> base, int exponent);
};

// different function with different input
std::vector<complex<double> > fft(std::vector<int> data, size_t N=0);
std::vector<std::complex<double> > fft(std::vector<double> data, size_t N=0);
std::vector<std::complex<double> > fft(std::vector<std::complex<double> > data, size_t N=0);

std::vector<std::complex<double> > ifft(std::vector<std::complex<double> > data, size_t N);
std::vector<std::complex<double> > ifft(std::vector<double> data, size_t N);
std::vector<std::complex<double> > ifft(std::vector<std::complex<double> > data, size_t N);

#endif // FFT_H
