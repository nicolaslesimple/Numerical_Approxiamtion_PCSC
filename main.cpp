/*! \mainpage Data Approximation
 *
 * This project helps user to approximate data that he can her-/himself plug into the program using the data.dat file.
 *
 * Currently two types of shapes can be drawn:
 * The most important application is in data fitting. The best fit in the least-squares sense minimizes the sum of squared
 * residuals (a residual being: the difference between an observed value, and the fitted value provided by a model). When
 * the problem has substantial uncertainties in the independent variable (the x variable), then simple regression and
 * least-squares methods have problems; in such cases, the methodology required for fitting errors-in-variables models
 * may be considered instead of that for least squares. The sum of the squares of the offsets is used instead of the
 * offset absolute values because this allows the residuals to be treated as a continuous differentiable quantity.
 * However, because squares of the offsets are used, outlying points can have a disproportionate effect on the fit,
 * a property which may or may not be desirable depending on the problem at hand.
 * Least-squares problems fall into two categories: linear or ordinary least squares and nonlinear least squares,
 * depending on whether or not the residuals are linear in all unknowns. The most common application of the least
 * squares method, referred to as linear or ordinary, aims to create a straight line that minimizes the sum of the
 * squares of the errors generated by the results of the associated equations, such as the squared residuals resulting
 * from differences in the observed value and the value anticipated based on the model. The coefficients and summary outputs
 * explain the dependence of the variables being tested.
 * Currently three major types of approximations can be performed:
 *
 * - \subpage LagrangePolynomial Functions "How to use the Lagrange method?"
 *
 * - \subpage FourierTransforms "How to does the Fourier Approximation works?"
 *
 * - \subpage LeastSquares "How to does the LeastSqaures Approximation works?"
 *
 */

/*! \page LagrangePolynomial How to use the Lagrange method?
 * Lagrange polynomials are used for polynomial interpolation. For a given set of points (xj,yj) for xi ̸= xj for all i, j.
 * The Lagrange polynomial is the polynomial of lowest degree that assumes at each value xj the corresponding value yj
 * (i.e. the functions coincide at each point).
 */

/*! \page FourierTransforms How to does the Fourier Approximation works?
 * Nowadays, the Fourier Transform (FT) is a major tool in all technical domains, raging for image processing to
 * telecommunication. Originally, by computing the FT of a function, the user decomposed a function of time into the
 * frequencies that made it up. The Fourier transform of a function of time is represented in the frequency domain.
 * However, the FT is not limited to functions of time, but in order to have a unified language, the domain of the
 * original function is commonly referred to as the time domain while the domain of the FT is referred to as the frequency
 * domain. For many functions, one can define an operation that reverses this: the inverse Fourier transformation of a
 * frequency domain representation combines the contributions of all the different frequencies to recover the original
 * function of time. The fact that one has the possibility to freely oscillate between the time and frequency domain
 * enables the user to compute certain operation which a demanding in the time domain more easily in the frequency
 * domain and then to switch back to the time domain to get the final output. However, in the frame of this project
 * it was possible to take advantage of the fact the Fourier Series are a way to represent a function as a superimposed
 * sum of simple sine waves with different frequencies. More formally, Fourier Series decompose any periodic function
 * into a superimposed sum of complex exponentials. The discrete- time Fourier transform (DFT) is a periodic function,
 * often defined in terms of a Fourier series.
 */

 /*! \page LeastSquares How to does the LeastSquares Approximation works?
 * The method of least squares is a standard approach in regression analysis to the approximate solution of overdetermined
 * systems, i.e., sets of equations in which there are more equations than unknowns. This method is a form of mathematical
 * regression analysis that finds the line of best fit for a dataset, providing a visual demonstration of the relationship
 * between the data points. Each point of data is representative of the relationship between a known independent variable
 * and an unknown dependent variable.
 */


/**
 * \file main.cpp
 * \brief This is the function to call to run the script of the project
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <complex>
#include "readFile.h"
#include "gnuplot_i.hpp"
#include "LeastSquare.h"
#include "Lagrange.h"
#include "Graph.h"
#include "FFTreal.h"
#include "Test.h"

using namespace std;

enum ApproxiamtionMethod {LEASTSQUARES, FOURIER, LAGRANGE,PIECEWISELEASTSQUARE,PIECEWISELAGRANGE};

int main()
{
    int choice_input;
    cout << "Welcome to David Cleres and Nicolas Lesimple data approximation tool. You have the choice between using a";
    cout << "config file or entering all the values by hand" << endl;
    cout << "1. Manual Entry" << endl;
    cout << "2. Read from config file" << endl;
    cout << "your choice is: " << flush;
    cin >> choice_input;

    size_t choice, choiceFunction;

    //Makes a copy of the input data since it is taken by reference in the rest of the program
    size_t degree;
    size_t intervalle;

    if (choice_input == 1)
    {
        cout << "Welcome to David Cleres and Nicolas Lesimple data approximation tool. You have the choice between using three";
        cout << " different approximation method which are:" << endl;
        cout << "1. Least Squares approximation" << endl;
        cout << "2. Fourier Approximation" << endl;
        cout << "3. Lagrange polynomial approximation" << endl;
        cout << "4. PieceWise Least Square approximation" << endl;
        cout << "5. PieceWise Lagrange approximation" << endl;
        cout << endl;
        cout << "Please select your approximation method by typing a number between 1 and 5" << endl;
        cout << "your choice is: " << flush;
        cin >> choice;

        cout << "Which function to you want to interpolate?" << endl;
        cout << "1. sin(x)" << endl;
        cout << "2. sin(x) + cos(3x)" << endl;
        cout << "your choice is: " << flush;
        cin >> choiceFunction;
    }
    else {
        std::string fnameConfig("/home/pcsc/Desktop/PCSC2017_Group5/data/config.dat");
        ReadFile readFileConfig(fnameConfig);
        vector<size_t> givenValues(readFileConfig.loadFromFileConfig());
        choice = givenValues[0];
        choiceFunction = givenValues[1];
        degree = givenValues[2];
        intervalle = givenValues[3];
    }

    std::string fname, fnameTest;
    if (choiceFunction == 1){ //the choice is sin(X)
        fname = ("/home/pcsc/Desktop/PCSC2017_Group5/data/data.dat");
        fnameTest = ("/home/pcsc/Desktop/PCSC2017_Group5/data/testData.dat");
    } else { //The choice is for sinx+cos3x
        fname = ("/home/pcsc/Desktop/PCSC2017_Group5/data/datasinxcos3x.dat");
        fnameTest = ("/home/pcsc/Desktop/PCSC2017_Group5/data/interpolationDataX.dat");
    }

    ReadFile readFile(fname);
    ReadFile readFileTest(fnameTest);

    //TRAINING VALUES
    vector<double> xs;
    vector<double> ys;
    Data data = {xs, ys};
    readFile.loadFromFile(data);
    //readFile.show(data); //SHOWS THE IMPORTED DATA

    //TEST VALUES
    vector<double> xsTest;
    vector<double> ysTest;
    Data dataTest = {xsTest, ysTest};
    readFileTest.loadFromFileTest(dataTest);
    //readFile.show(data); //SHOWS THE IMPORTED DATA

    Data data_original = data;

    Graph graph(data); // use to make all the graph

    ApproxiamtionMethod usersApproxChoice;

    try {
        //Convert the given Number to enum type
        switch(choice)
        {
            case 1: usersApproxChoice = LEASTSQUARES;
                break;
            case 2: usersApproxChoice = FOURIER;
                break;
            case 3: usersApproxChoice = LAGRANGE;
                break;
            case 4: usersApproxChoice = PIECEWISELEASTSQUARE;
                break;
            case 5: usersApproxChoice = PIECEWISELAGRANGE;
                break;

            default: throw string("ERREUR: The user did not specified a number in the given boundaries");
        }
    } catch (string const& e) {
        usersApproxChoice = FOURIER;
        cout << "The approximation method has been set to: Fourier Approximation";
    }

    switch(usersApproxChoice) {
        case LEASTSQUARES: {
            cout << "LEAST SQUARES" << endl;
            if (choice_input == 1) {
                cout << "Choose the degree of approximation you want. It must be an integer :  " << flush;
                cin >> degree;
            }
            graph.make_graph_least_square(degree);
        } break;

        case LAGRANGE: {
            cout << "LAGRANGE" << endl;
            graph.make_graph_lagrange();
        } break;

        case FOURIER: {
            cout << "FOURIER" << endl;
            graph.make_graph_FFT(dataTest);
        }   break;

        case PIECEWISELEASTSQUARE: {
            cout << "PIECEWISE LEAST SQUARE" << endl;
            if (choice_input == 1) {
                cout << "Choose the degree of approximation you want. It must be an integer :  " << flush;
                cin >> degree;
                cout << "Choose the number of interval for your approximation you want. It must be an even integer :  "
                     << flush;
                cin >> intervalle;
            }
            graph.make_graph_piece_wise_least_squares(degree,intervalle);
        }   break;

        case PIECEWISELAGRANGE: {
            cout << "PIECEWISE LAGRANGE" << endl;
            if (choice_input == 1) {
                cout << "Choose the number of interval for your approximation you want. It must be an even integer :  "
                     << flush;
                cin >> intervalle;
            }
            graph.make_graph_piece_wise_lagrange(intervalle);
        }   break;
    }

    //TESTING
    cout << "Testing Starts ..." << endl;
    Test test;

    cout << "==================== TEST RESULTS ===============================" << endl;
    cout << "FOURIER: The fraction of correctly interpolated values is: " << test.testFourier() << endl;
    cout << "LEAST SQUARES: The fraction of correctly interpolated values is: " << test.testLeastSquares() << endl;
    cout << "LAGRANGE: The fraction of correctly interpolated values is: " << test.testLagrange() << endl;
    cout << "LEAST SQUARES PIECEWISE: The fraction of correctly interpolated values is: " << test.testLeastSquaresPieceWise() << endl;
    cout << "LAGRANGE PIECEWISE: The fraction of correctly interpolated values is: " << test.testLagrangePiecewise() << endl;
    cout << "==================== TEST FINISHED ==============================" << endl;

    return 0;
}