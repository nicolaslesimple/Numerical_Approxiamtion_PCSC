#include <iostream>
#include <cmath>
#include "readFile.h"
#include "PieceWiseContinuePolynomial.h"
#include "LeastSquare.h"
#include "Lagrange.h"

using namespace std ;

vector<vector<double>> PieceWiseContinuePolynomial::solve_lagrange_degree(size_t const& degree, vector<double> const& x_plot) const
{
    size_t N  (mData.heights.size());
    size_t nb_intervalle (degree+1);
    size_t Intervalle(N/(degree+1));
    size_t reste(N%(degree+1));
    vector<vector<double>> x(Intervalle, vector<double>(0));                                     //We declare the matrix that we will need to store in each line each point of just one interval.
    vector<vector<double>> y(Intervalle, vector<double>(0));                                    //Each line correspond to one interval and each colunm in one line correspond to one point in the interval
    for (size_t i(1); i <= Intervalle; ++i) {
        for (size_t j((nb_intervalle) * (i - 1)); j <= (nb_intervalle * i); ++j) {          //We use push back to avoid problem with index and thus we enter the points of one interval in each line
            x[i - 1].push_back(mData.heights[j]);
            y[i - 1].push_back(mData.weights[j]);
            if (i == Intervalle and reste != 0 and j==nb_intervalle*Intervalle) {        //We have separate the data in a number of intervals by using the degree and the number of points in the dataset
                for (size_t z(1); z < reste; z++) {                                      //It's possible that the division is not perfect and thus we need to take into account the residue.
                    x[i - 1].push_back(mData.heights[j + z]);                            //The residue correspond to some points that we will put in the last interval as you can see on this for loop with the condition.
                    y[i - 1].push_back(mData.weights[j + z]);                            //These conditions make us know that we are on the last interval and that there is a residue.
                }
            }
        }
    }
    vector<vector<double>> approx(2,vector<double>(0));                                      //We declare the matrix that we will return. It's a matrix with two line where the first line correspond to the x and the second line to the y
    for (int i(1); i <= Intervalle; i++) {
        vector<double> tmpx(0);                                                              //We will use vector to take each line of the matrix x and y to then apply it on the lagrange function.
        vector<double> tmpy(0);
        for (int j = 0; j <=nb_intervalle; ++j) {
            tmpx.push_back(x[i - 1][j]);                                                    //We fill the tmp vectors
            tmpy.push_back(y[i - 1][j]);
            if(reste!=0 and i==Intervalle and j==nb_intervalle){                            //We take into account that if there is a reste, the last interval as more points than the others.
                for (size_t z(1); z<reste;++z){
                    tmpx.push_back(x[i - 1][j+z]);
                    tmpy.push_back(y[i - 1][j+z]);
                }
            }
            if (tmpx[j]==0){                                                                //Sometimes due to index and due to different choice of degree we have 0 in addition to what we want in the tmp. Thus we delete it because we don't want a 0.
                tmpx.pop_back();
                tmpy.pop_back();
            }
        }
        Lagrange lagrange;                                                                  //We declare an object of type Lagrange which will allow us to use the function lagrange and thus solve our problem.
        for (size_t k(0); k < x_plot.size(); ++k) {                                         //We apply Lagrange method on the data of the interval.
            if (x_plot[k]>=tmpx[0] and x_plot[k]<tmpx[(tmpx.size()-1)]) {
                approx[0].push_back(x_plot[k]);                                             //We fill up our matrix of return with the x corresponding to the y which are the approximation.
                approx[1].push_back(lagrange.solve(tmpx, tmpy, x_plot[k]));
            }
        }
    }
    return approx;                                                                          //We return our matrix containing x and y to plot.
}


vector<vector<double>> PieceWiseContinuePolynomial::solve_least_square_degree(size_t const& degree, size_t const& Intervalle,vector<double> const& x_plot) const
{
    size_t N  (mData.heights.size());
    size_t nb_intervalle (N / Intervalle);
    size_t reste(N%Intervalle);
    vector<vector<double>> x(Intervalle, vector<double>(0));                                     //We declare the matrix that we will need to store in each line each point of just one interval.
    vector<vector<double>> y(Intervalle, vector<double>(0));                                    //Each line correspond to one interval and each colunm in one line correspond to one point in the interval
    for (size_t i(1); i <= Intervalle; ++i) {
        for (size_t j((nb_intervalle) * (i - 1)); j <= (nb_intervalle * i); ++j) {          //We use push back to avoid problem with index and thus we enter the points of one interval in each line
            x[i - 1].push_back(mData.heights[j]);
            y[i - 1].push_back(mData.weights[j]);
            if (i == Intervalle and reste != 0 and j==nb_intervalle*Intervalle) {           //We have separate the data in a number of intervals by using the degree and the number of points in the dataset
                for (size_t z(1); z < reste; z++) {                                         //It's possible that the division is not perfect and thus we need to take into account the residue.
                    x[i - 1].push_back(mData.heights[j + z]);                               //The residue correspond to some points that we will put in the last interval as you can see on this for loop with the condition.
                    y[i - 1].push_back(mData.weights[j + z]);                               //These conditions make us know that we are on the last interval and that there is a residue.
                }
            }
        }
    }
    vector<vector<double>> approx(2,vector<double>(0));                                      //We declare the matrix that we will return. It's a matrix with two line where the first line correspond to the x and the second line to the y
    for (int i(1); i <= Intervalle; i++) {
        vector<double> tmpx(0);                                                              //We will use vector to take each line of the matrix x and y to then apply it on the lagrange function.
        vector<double> tmpy(0);
        for (int j = 0; j <=nb_intervalle; ++j) {
            tmpx.push_back(x[i - 1][j]);                                                    //We fill the tmp vectors
            tmpy.push_back(y[i - 1][j]);
            if(reste!=0 and i==Intervalle and j==nb_intervalle){                            //We take into account that if there is a reste, the last interval as more points than the others.
                for (size_t z(1); z<reste;++z){
                    tmpx.push_back(x[i - 1][j+z]);
                    tmpy.push_back(y[i - 1][j+z]);
                }
            }
            if (tmpx[j]==0){                                                                //Sometimes due to index and due to different choice of degree we have 0 in addition to what we want in the tmp. Thus we delete it because we don't want a 0.
                tmpx.pop_back();
                tmpy.pop_back();
            }
        }

        Polynomial polynomial;                                                               //We declare an object of type Least Square which will allow us to use the function Least square and thus solve our problem.
        vector<double> a(polynomial.solve(tmpx, tmpy, degree));
        for (size_t k(0); k < x_plot.size(); ++k) {                                         //We apply Least Square method on the data of the interval.
            if (x_plot[k]>=tmpx[0] and x_plot[k]<tmpx[(tmpx.size()-1)]) {
                double answer(0);
                for (int z = 0; z < (degree + 1); z++) {
                    answer += pow(x_plot[k], z) * a[z];
                }
                approx[0].push_back(x_plot[k]);                                             //We fill up our matrix of return with the x corresponding to the y which are the approximation.
                approx[1].push_back(answer);
            }
        }

    }
    return approx;                                                                          //We return our matrix containing x and y to plot.
}


PieceWiseContinuePolynomial::PieceWiseContinuePolynomial(Data const &data)
:mData(data)
{}
