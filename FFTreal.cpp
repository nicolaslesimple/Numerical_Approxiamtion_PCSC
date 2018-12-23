/**
 * \file main.cpp
 * \brief This is the function to call to run the script of the project
 */

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <iostream>
#include "FFTreal.h"

using std::size_t;
using std::vector;

// Private function prototypes
static size_t reverseBits(size_t x, int n);

void FFTreal::transform(vector<double> &real, vector<double> &imag) {
    size_t n = real.size();
    if (n != imag.size())
        throw "Mismatched lengths";
    if (n == 0)
        return;
    else if ((n & (n - 1)) == 0)  // Is power of 2
        /*n & (n - 1) unset the lower set bit of n
          in binary: XXX10000 -> XXX00000
          So (n & (n - 1)) == 0 for 0 and all powers of 2.
          n & (n - 1) == 0:
          n & (n - 1) == 0 is equivalent to n & ((n - 1) == 0) (due to precedence of operator) and so n == 1.*/
        transformRadix2(real, imag);
    else  // More complicated algorithm for arbitrary sizes
        transformBluestein(real, imag);
}

void FFTreal::transformCoefs(vector<double> const& real, vector<double>& an, vector<double>& bn, size_t const& period) {

    size_t N (real.size()); //number of ak et bk computed

    bn[0] = 0.0;
    for(size_t k(0); k < an.size(); k++) {
        for (int i(0); i < N; i++) {
            if (k == 0) {
                an[k] += 2.0 / N * (real[i]);

            } else {
                an[k] += 2.0 / N * (real[i]) * cos(2.0 * M_PI * i * k / N);
                bn[k] += 2.0 / N * (real[i]) *
                         sin(2.0 * M_PI * i * k / N); //on a un intervalle de N et pas de 2L
            }
        }
    }
}

vector<double> FFTreal::transformApproximation(vector<double>const& an, vector<double>const& bn, size_t const& period, vector<double>& real) {
    vector<double> approximation(real.size(), 0.0);
    size_t N(real.size());
    for (size_t i(0); i < real.size(); i++) {
        approximation[i] = an[0];
        for(size_t k(1); k < an.size(); k++) {
            approximation[i] += an[k]*cos(2.0*M_PI*i*k/N)+bn[k]*sin(2.0*M_PI*i*k/N);
        }
        approximation[i] += an[an.size()-1] * cos(2.0*M_PI*i);
    }
    return approximation;
}

void FFTreal::inverseTransform(vector<double> &real, vector<double> &imag) {
    transform(imag, real);
}

void FFTreal::transformRadix2(vector<double> &real, vector<double> &imag) {
    // Length variables
    size_t n = real.size();
    if (n != imag.size())
        throw "Mismatched lengths";
    int levels = 0;  // Compute levels = floor(log2(n))
    for (size_t temp = n; temp > 1U; temp >>= 1)
        levels++;
    if (static_cast<size_t>(1U) << levels != n)
        throw "Length is not a power of 2";

    // Trignometric tables
    vector<double> cosTable(n / 2);
    vector<double> sinTable(n / 2);
    for (size_t i = 0; i < n / 2; i++)
    {
        cosTable[i] = std::cos(2 * M_PI * i / n);
        sinTable[i] = std::sin(2 * M_PI * i / n);
    }

    // Bit-reversed addressing permutation
    for (size_t i = 0; i < n; i++) {
        size_t j = reverseBits(i, levels);
        if (j > i) {
            std::swap(real[i], real[j]);
            std::swap(imag[i], imag[j]);
        }
    }

    // Cooley-Tukey decimation-in-time radix-2 FFT
    for (size_t size = 2; size <= n; size *= 2) {
        size_t halfsize = size / 2;
        size_t tablestep = n / size;
        for (size_t i = 0; i < n; i += size) {
            for (size_t j = i, k = 0; j < i + halfsize; j++, k += tablestep) {
                size_t l = j + halfsize;
                double tpre =  real[l] * cosTable[k] + imag[l] * sinTable[k];
                double tpim = -real[l] * sinTable[k] + imag[l] * cosTable[k];
                real[l] = real[j] - tpre;
                imag[l] = imag[j] - tpim;
                real[j] += tpre;
                imag[j] += tpim;
            }
        }
        if (size == n)  // Prevent overflow in 'size *= 2'
            break;
    }
}

void FFTreal::transformBluestein(vector<double> &real, vector<double> &imag) {
    // Find a power-of-2 convolution length m such that m >= n * 2 + 1
    size_t n = real.size();
    if (n != imag.size())
        throw "Mismatched lengths";
    size_t m = 1;
    while (m / 2 <= n) {
        if (m > SIZE_MAX / 2)
            throw "Vector too large";
        m *= 2;
    }

    // Trigonometric tables
    vector<double> cosTable(n), sinTable(n);
    for (size_t i = 0; i < n; i++) {
        unsigned long long temp = static_cast<unsigned long long>(i) * i;
        temp %= static_cast<unsigned long long>(n) * 2;
        double angle = M_PI * temp / n;
        // Less accurate alternative if long long is unavailable: double angle = M_PI * i * i / n;
        cosTable[i] = std::cos(angle);
        sinTable[i] = std::sin(angle);
    }

    // Temporary vectors and preprocessing
    vector<double> areal(m), aimag(m);
    for (size_t i = 0; i < n; i++) {
        areal[i] =  real[i] * cosTable[i] + imag[i] * sinTable[i]; //an
        aimag[i] = -real[i] * sinTable[i] + imag[i] * cosTable[i];
    }
    vector<double> breal(m), bimag(m);
    breal[0] = cosTable[0];
    bimag[0] = sinTable[0];
    for (size_t i = 1; i < n; i++) {
        breal[i] = breal[m - i] = cosTable[i]; //bn
        bimag[i] = bimag[m - i] = sinTable[i];
    }

    // Convolution between a and b is put in c
    vector<double> creal(m), cimag(m);
    convolve(areal, aimag, breal, bimag, creal, cimag);

    // Postprocessing
    for (size_t i = 0; i < n; i++) {
        real[i] =  creal[i] * cosTable[i] + cimag[i] * sinTable[i];
        imag[i] = -creal[i] * sinTable[i] + cimag[i] * cosTable[i];
    }
}

void FFTreal::convolve(const vector<double> &x, const vector<double> &y, vector<double> &out) {
    size_t n = x.size();
    if (n != y.size() || n != out.size())
        throw "Mismatched lengths";
    vector<double> outimag(n);
    convolve(x, vector<double>(n), y, vector<double>(n), out, outimag);
}

void FFTreal::convolve(
        const vector<double> &xreal, const vector<double> &ximag,
        const vector<double> &yreal, const vector<double> &yimag,
        vector<double> &outreal, vector<double> &outimag) {

    size_t n = xreal.size();
    if (n != ximag.size() || n != yreal.size() || n != yimag.size()
        || n != outreal.size() || n != outimag.size())
        throw "Mismatched lengths";

    vector<double> xr = xreal;
    vector<double> xi = ximag;
    vector<double> yr = yreal;
    vector<double> yi = yimag;
    transform(xr, xi);
    transform(yr, yi);

    for (size_t i = 0; i < n; i++) {
        double temp = xr[i] * yr[i] - xi[i] * yi[i];
        xi[i] = xi[i] * yr[i] + xr[i] * yi[i];
        xr[i] = temp;
    }
    inverseTransform(xr, xi);

    for (size_t i = 0; i < n; i++) {  // Scaling (because this FFT implementation omits it)
        outreal[i] = xr[i] / n;
        outimag[i] = xi[i] / n;
    }
}

static size_t reverseBits(size_t x, int n) {
    size_t result = 0;
    for (int i = 0; i < n; i++, x >>= 1)
        result = (result << 1) | (x & 1U);
    return result;
}