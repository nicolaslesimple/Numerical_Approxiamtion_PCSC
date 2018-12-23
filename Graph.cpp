#include <iostream>
#include <cmath>
#include "Graph.h"
#include "LeastSquare.h"
#include "gnuplot_i.hpp"
#include "PieceWiseContinuePolynomial.h"
#include "Lagrange.h"
#include "FFTreal.h"

Graph :: Graph(Data const& data)
: mData(data)
{}

////////////////LeastSquare//////////////////////////////
void Graph :: make_graph_least_square(size_t const& degree) const
{
    Polynomial poly;
    vector <double> a (poly.solve(mData.heights,mData.weights, degree));                  // we found the coefficient by the least square method minimizibg the loss. a is a vector with the coefficients searched.
    vector<double>x(make_x_points());
    vector<double>y(x.size());

    cout<< "The interpolation polynome is : ";
    for (size_t i(0); i < (degree+1);i++){
        cout<<" + ("<<a[i]<<")"<<"x^"<<i;
    }

    for (size_t j(0); j<x.size(); ++j)
    {
        for (size_t i(0); i < (degree+1); i++)
        {
            y[j]+=pow(x[j],i)*a[i];                                                     //we apply the least square coefficient to find the approimation
        }
    }
    ///Plot///
    make_graph(x,y);
}

/////////////////////////Lagrange/////////////////////////////
void Graph :: make_graph_lagrange() const {
    vector<double> x(make_x_points());
    vector<double> y(x.size());
    Lagrange lagrange;
    for (size_t j(0); j < x.size(); ++j) {
        y[j] = lagrange.solve(mData.heights, mData.weights, x[j]);                  //we apply the lagrange formula to each augmented set of x points.
    }

    ///Plot///
    make_graph(x,y);
}
/////////////////////////PieceWise Least Square/////////////////////////////
void Graph :: make_graph_piece_wise_least_squares(size_t const& degree, size_t const& Intervalle) const
{
    vector<double>x(make_x_points());
    PieceWiseContinuePolynomial piece (mData);
    vector<vector<double>>point(piece.solve_least_square_degree(degree, Intervalle,x));         //We apply piece wise least square method.
    ///Plot///
    make_graph(point[0],point[1]);
}
/////////////////////////Piece Wise Lagrange/////////////////////////////
void Graph :: make_graph_piece_wise_lagrange(size_t const& intervalle) const
{
    vector<double>x(make_x_points());
    PieceWiseContinuePolynomial piece (mData);
    vector <vector<double>> approx(piece.solve_lagrange_degree(intervalle, x));     //We apply piece wise Lagrange method.
    ///Plot///
    make_graph(approx[0],approx[1]);
}
/////////////////////////FOURIER/////////////////////////////
void Graph :: make_graph_FFT(Data data_original)
{
    Data tmp = mData;
    //////////////////////// COMPUTE THE FFT /////////////////////////////////////////////////
    FFTreal fft;
    vector<double> imaginary_part(mData.heights.size(), 0.0);
    fft.transform(mData.weights, imaginary_part);

    vector<double> ifft(mData.weights);
    fft.inverseTransform(ifft, imaginary_part);

    //////////////////////// COMPUTE THE FOURIER APPROXIMATION ////////////////////////////////
    size_t nbK(mData.weights.size()); //number of ak and bk to compute
    vector<double> an(nbK, 0.0);
    vector<double> bn(nbK, 0.0);

    //we used cos(pi*x which has a period of 2
    fft.transformCoefs(tmp.weights, an, bn, 2);
    vector<double> approx(fft.transformApproximation(an, bn, 2, data_original.weights));

    for (auto &element : ifft) {
        element /= ifft.size();
    }

    //on doit plotter data_copy où on a changé les valeurs des x associée aux y.
    Gnuplot g1 = Gnuplot("lines");
    g1.set_style("points");
    g1.plot_xy(tmp.heights, mData.weights, "FFT");
    sleep(2);
    g1.plot_xy(tmp.heights, ifft, "Inverse FFT");
    sleep(2);
    //g1.plot_xy(tmp.heights, tmp.weights, "Default points"); //LOADS THE POINTS OF THE DATA SET
    //sleep(2);
    g1.plot_xy(data_original.weights, approx, "Fourier");
    sleep(20);
}

vector<double> Graph :: make_x_points() const{
    vector<double>x(10*(mData.heights.size()-1));                                            //The for loop help us to augment the number of point on which we will apply our approximation
    for(size_t count(0);count< (mData.heights.size()-1);++count) {
        for (size_t d(0); d < 10; ++d) {
            x[count*10+d] = (((mData.heights[count+1]-mData.heights[count])/ 10) * d) + mData.heights[count];
        }
    }
    return x;
}

void Graph::make_graph(vector<double> const& x, vector<double>const& y) const {
    Gnuplot g1 = Gnuplot("lines");
    g1.set_style("points");
    g1.plot_xy(x,y,"Approximation");
    sleep(2);
    g1.plot_xy(mData.heights, mData.weights,"Default points");
    sleep(20);
}