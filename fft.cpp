#include "fft.h"

size_t calcN(size_t length) {
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

complex<double> pow(complex<double> base, int exponent) {
  // return base^{exponent}
    complex<double> temp = 1;
    for(int i = 0; i < exponent; i++)
        temp *= base;
    return temp;
}


std::vector<complex<double> > fft(vector<int> data, size_t N)
{
  // convert data to vector<complex<double> >
  // call:
  // vector<complex<double> >
  // fft(vector<complex<double> > data, size_t N)

    vector<complex<double> > d(data.size());
    for(int i = 0;i < data.size();i++)
    {
        d.at(i) = data.at(i);
    }
    return fft(d, N);
}

vector<complex<double> >
fft(vector<double> data, size_t N)
{

  // convert data to vector<complex<double> >
  // call:
  // vector<complex<double> >
  // fft(vector<complex<double> > data, size_t N)

//    calloc(data, vector<complex<double>>);
    vector<complex<double> > d(data.size());
    for(int i = 0;i < data.size();i++)
    {
        d.at(i) = data.at(i);
    }
    return fft(d, N);
}

vector<complex<double> >
fft(vector<complex<double> > data, size_t N) {

  // check length of data, and append 0 if neccessary

  // start fft
  // check if N is 0, 1, 2
  // if N is 0 or 1, just return data
  // if N is 2, do dft on them
  // if N > 2, do fft
    // 1. split input into two parts
    // 2. do fft on them seperately
    // 3. construct result from output

    if(N == 0) N = calcN(data.size());

    if((N & (N - 1)) != 0) {
        cout << "error N" << endl;
        return data;
    }

    size_t delta = N - data.size();
    while (delta--) {
        data.push_back(complex<double>(0, 0));
    }

    vector<complex<double> > d(data.size()/2);
    vector<complex<double> > s(data.size()/2);
    vector<complex<double> > d1(data.size()/2);
    vector<complex<double> > s1(data.size()/2);
    vector<complex<double> > e(data.size());

    if(N == 0 || N == 1) return data;
    else if(N == 2)
    {
        e.at(0) = data.at(0) + data.at(1);
        e.at(1) = data.at(0) - data.at(1);
    }
    else if(N > 2)
    {
        for(int i = 0; i < data.size(); i+=2)
        {
            d.at(i/2) = data.at(i);
            s.at(i/2) = data.at(i + 1);
        }

        d1 = fft(d, calcN(d.size()));
        s1 = fft(s, calcN(s.size()));

        complex<double> w(cos(-2*PI/N), sin(-2*PI/N));

        for(int i = 0; i <N/2; i++)
        {
            e.at(i) = d1.at(i) + pow(w, i) * s1.at(i);
            e.at(i + N/2) = d1.at(i) - pow(w, i) * s1.at(i);
        }
    }
    return e;
}

vector<complex<double> >
ifft(vector<complex<double> > data, size_t N) {
    if(N == 0) N = calcN(data.size());

    if((N & (N - 1)) != 0) {
        cout << "error N" << endl;
        return data;
    }

    size_t temp = data.size();
    if(temp < N)
        for(int i = temp; i < N; i++)
            data.push_back(complex<double>(0, 0));

    vector<complex<double> > e(data.size());

    for(int i = 0; i < N; i++)
    {
        complex<double> temp(data.at(i).real(), -data.at(i).imag());
        e.at(i) = temp;
    }

    vector<complex<double> > ret = fft(e);

    for(int i = 0; i < N; i++)
    {
        complex<double> temp(ret.at(i).real()/N, -ret.at(i).imag()/N);
        e.at(i) = temp;
    }

    return e;
}

std::vector<complex<double> >
ifft(vector<int> data, size_t N)
{
  // convert data to vector<complex<double> >
  // call:
  // vector<complex<double> >
  // fft(vector<complex<double> > data, size_t N)

    vector<complex<double> > d(data.size());
    for(int i = 0;i < data.size();i++)
    {
        d.at(i) = data.at(i);
    }
    return ifft(d, N);
}

vector<complex<double> >
ifft(vector<double> data, size_t N)
{

  // convert data to vector<complex<double> >
  // call:
  // vector<complex<double> >
  // fft(vector<complex<double> > data, size_t N)

//    calloc(data, vector<complex<double>>);
    vector<complex<double> > d(data.size());
    for(int i = 0;i < data.size();i++)
    {
        d.at(i) = data.at(i);
    }
    return ifft(d, N);
}
