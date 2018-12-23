#include <cassert>
#include <iostream>
#include "readFile.h"
#include "Lagrange.h"

using namespace std ;

/// Polynomial approximation by the Lagrange algorithm
double Lagrange::solve(vector<double> const& data_x,vector<double> const& data_y,double xi) {

size_t n (data_x.size());                                                                  // function to interpolate the given data points using Lagrange's formula
double result = 0; // Initialize result                                                    // xi corresponds to the new data point whose value is to be obtained
                                                                                            // n represents the number of known data points
    for (size_t i(0); i < n; i++) {
        double term = data_y[i];                                                            // Compute individual terms of above formula
        for (size_t j = 0; j < n; j++) {
            if (j != i)
                term = term * (xi - data_x[j]) / (data_x[i] - data_x[j]);
        }
        result += term;                                                                      // Add current term to result
    }

    return result;
}
