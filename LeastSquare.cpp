/**
 * \file Polynomial.cpp
 * \brief This is the function to call to run the script of the project
 */

#include <cmath>
#include <iostream>
#include "readFile.h"
#include "LeastSquare.h"

/// Polynomial approximation of the given points using a single polynome
vector<double> Polynomial::solve(vector<double> const& data,vector<double> const& data_y, size_t const& degree)
{
    // n is the degree of Polynomial
    size_t N (data.size());
    size_t n (degree);
    vector<double> X(2*n+1);                        //Array that will store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    for (size_t i(0); i < 2*n+1; i++)
    {
        X[i]=0;
        for (size_t j(0);j < N;j++)
        {
            X[i]=X[i]+pow(data[j],i);
        }                                           //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    }

    vector<vector<double>>B((n+1),vector<double>(n+2));
    vector<double>a(n+1);                           //B is the Normal matrix(augmented) that will store the equations, 'a' is for value of the final coefficients
    for (size_t i(0); i <= n; i++)
    {
        for (size_t j(0); j <= n;j++)
        {
            B[i][j]=X[i+j];
        }
    }                                               //Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix
    vector<double> Y(n+1);                          //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    for (size_t i(0);i < n+1; i++)
    {
        Y[i]=0;
        for (size_t j(0); j < N;j++)
        {
            Y[i]=Y[i]+pow(data[j],i)*data_y[j];
        }                                           //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    }
    for (size_t i(0);i <= n;i++)
    {
        B[i][n+1]=Y[i];
    }                                               //load the values of Y as the last column of B(Normal Matrix but augmented)
    n=n+1;                                          //n is made n+1 because the Gaussian Elimination part below was for n equations, but here n is the degree of polynomial and for n degree we get n+1 equations
    for (size_t i(0);i < n-1; i++)
    {                                               //loop to perform the gauss elimination
        for (size_t k(i+1);k<n;k++)
        {
            double t=B[k][i]/B[i][i];
            for (size_t j(0);j <= n;j++){
                B[k][j]=B[k][j]-t*B[i][j];
            }                                       //make the elements below the pivot elements equal to zero or elimnate the variables
        }
    }
    for (int i(n-1); i >= 0; i--)                   //back-substitution we had to keep i as an int otherwise we have a problem at the loop temrination
    {                                               //x is an array whose values correspond to the values of x,y,z..
        a[i]=B[i][n];                               //make the variable to be calculated equal to the rhs of the last equation
        for (size_t j(0); j < n;j++)
        {
            if (j != i) {                           //then subtract all the lhs values except the coefficient of the variable whose value is being calculated
                a[i] = a[i] - B[i][j] * a[j];
            }
        }
        a[i]=a[i]/B[i][i];                          //now finally divide the rhs by the coefficient of the variable to be calculated
    }
    return a;
}