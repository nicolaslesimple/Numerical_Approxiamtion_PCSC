/**
 * \brief This is redefinition of the virtual class to implement Lagrange functions
 * \class Lagrange
 * This is how we can calculate the approximation of the data using Lagrange Polynome
 */
/**
 * \class FFTreal
 *
 * \ingroup PackageName
 * (Note, this needs exactly one \defgroup somewhere)
 *
 * \brief This is the function to call to perform the FFT of a given set of values but also to implement the data
 * approximation by computing the fourier series coefficients.
 *
 * \file Lagrange.h
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

#ifndef PCSC2017_GROUP5_LAGRANGE_H
#define PCSC2017_GROUP5_LAGRANGE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "readFile.h"

using namespace std;

///@class
class Lagrange{

public:

    /**\brief Lagrange return directly the point corresponding to the argument xi
     * \param data_x is a vector with the values read from the data.dat file
     * \param data_y is a vector with the values read from the data.dat file, if we have only real entries then you have to
     * specify a vector with the same size as real but filled with zeros.
     * \param xi
     */
    double solve(vector<double> const& data_x,vector<double> const& data_y,double xi);

private:

};

#endif //PCSC2017_GROUP5_LAGRANGE_H