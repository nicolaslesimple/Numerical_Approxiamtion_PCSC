/**
 * \class Polynomial
 *
 * \ingroup PackageName
 * (Note, this needs exactly one \defgroup somewhere)
 *
 * \brief This is the function to call to perform the FFT of a given set of values but also to implement the data
 * approximation by computing the fourier series coefficients.
 *
 * \file Polynomial.h
 *
 * \note Optional part of the project
 *
 * \author (last to touch it) $Author: DC & NL$
 *
 * \version $Revision: 1.0 $
 *
 * \date $Date: 2017.12.10 $
 *
 * Contact: david.cleres@epfl.ch & nicolas.lesimple@epfl.ch
 *
 */

#ifndef PROJECT_POLYNOMIAL_H
#define PROJECT_POLYNOMIAL_H

#include <array>

using namespace std ;

///@class
class Polynomial {

public:

    /** \brief solve the linear equation
     * \param data is a vector with the values of approximate (x-axis)
     * \param degree is the degree of the polynome
     * \param data_y is a vector with the values of approximate (y-axis)
     */
    vector<double> solve(vector<double> const& data,vector<double> const& data_y, size_t const& degree);
};

#endif //PROJECT_POLYNOMIAL_H