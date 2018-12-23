/**
 * \class PieceWiseContinuePolynomial
 *
 * \ingroup PackageName
 * (Note, this needs exactly one \defgroup somewhere)
 *
 * \brief This is the function to call to perform the Least Square Regression by pieces  of a given set of values
 *
 * \file PieceWiseContinuePolynomial.h
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

#ifndef PROJECT_PIECEWISE_CONTINUE_POLYNOMIAL_H
#define PROJECT_PIECEWISE_CONTINUE_POLYNOMIAL_H

#include <iostream>
#include <cassert>
#include <cmath>
#include "readFile.h"

using namespace std;

///@class
class PieceWiseContinuePolynomial {

public:

    /**\brief Constructor
     * \param data is the input value from the files
     */
    explicit PieceWiseContinuePolynomial(Data const& data);

    /**\brief
     * \param degree degree of the polynome
     * \param Intervale
     * \param x_plot gives the x axis values of the plot
     * \return matrix containing the solved linear system
     */
    vector<vector<double>> solve_least_square_degree(size_t const& degree, size_t const& Intervalle, vector<double> const& x_plot) const;

    /**\brief solves by using lagrange
     * \param Intervalle
     * \param x_plot gives the x axis values of the plot
     * \return matrix containing the solved linear system
     */
    vector<vector<double>> solve_lagrange_degree(size_t const& Intervalle, vector<double> const& x_plot) const;

private:
    Data mData;
};

#endif //PROJECT_PIECEWISE_CONTINUE_POLYNOMIAL_H