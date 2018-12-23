#include "Test.h"
#include "gnuplot_i.hpp"
#include "Graph.h"


double Test::testFourier() {
    FFTreal fft;
    size_t nbK(mApproxData.weights.size()); //number of ak and bk to compute
    vector<double> an(nbK, 0.0);
    vector<double> bn(nbK, 0.0);

    fft.transformCoefs(mApproxData.weights, an, bn, 2);
    mDataToApproximate.heights = fft.transformApproximation(an, bn, 2, mDataToApproximate.weights);

    size_t counter(0);

    for (size_t i(0); i < mDataToApproximate.weights.size(); i++) {
        if (mDataToApproximate.heights[i] == mRealData.weights[i]) {
            counter++;
        }
    }

    //on doit plotter data_copy où on a changé les valeurs des x associée aux y.
    Gnuplot g1 = Gnuplot("lines");
    g1.set_style("points");
    g1.plot_xy(mDataToApproximate.weights, mDataToApproximate.heights, "Approximation");
    sleep(2);
    g1.plot_xy(mRealData.heights, mRealData.weights, "Real Data");
    sleep(5);

    double counterDouble(counter);

    return counterDouble / mDataToApproximate.weights.size();
}

Test::Test()
{
    //TRAINING VALUES
    vector<double> xs;
    vector<double> ys;
    Data data = {xs, ys};

    mApproxData = data;
    mRealData = data;
    mDataToApproximate = data;

    //INIT THE VECTORS
    string filenameApprox("/home/pcsc/Desktop/PCSC2017_Group5/data/data.dat");
    string filenameReal("/home/pcsc/Desktop/PCSC2017_Group5/data/realDataSin.dat");
    string filenameTest("/home/pcsc/Desktop/PCSC2017_Group5/data/dataInterpolationX.dat");
    ReadFile readFileApprox(filenameApprox);
    ReadFile readFileReal(filenameReal);
    ReadFile readFileTest(filenameTest);
    readFileApprox.loadFromFile(mApproxData);           //Data to train the model
    readFileReal.loadFromFile(mRealData);               //Actual Data
    readFileTest.loadFromFileTest(mDataToApproximate);  //data to interpolate
}

double Test::testLeastSquares() const
{
    Graph graph(mApproxData);
    Polynomial poly;
    vector <double> a (poly.solve(mApproxData.heights,mApproxData.weights, mDegree_leastsquare));     // we found the coefficient by the least square method minimizibg the loss. a is a vector with the coefficients searched.
    vector<double>x(graph.make_x_points());
    vector<double>y(x.size());

    cout<< "The interpolation polynome is : ";
    for (size_t i(0); i < (mDegree_leastsquare+1);i++){
        cout<<" + ("<<a[i]<<")"<<"x^"<<i;
    }
    for (size_t j(0); j<x.size(); ++j) {
        for (size_t i(0); i < (mDegree_leastsquare + 1); i++) {
            y[j] += pow(x[j], i) *
                    a[i];                                              //we apply the least square coefficient to find the approimation
        }
    }
    return generate_test(x,y);
}

double Test::testLagrange() const
{
    Graph graph(mApproxData);
    vector<double> x(graph.make_x_points());
    vector<double> y(x.size());
    Lagrange lagrange;
    for (size_t j(0); j < x.size(); ++j) {
        y[j] = lagrange.solve(mApproxData.heights, mApproxData.weights, x[j]);      //we apply the lagrange formula to each augmented set of x points.
    }
    return generate_test(x,y);
}

double Test::testLeastSquaresPieceWise() const
{
    Graph graph(mApproxData);
    vector<double>x(graph.make_x_points());
    PieceWiseContinuePolynomial piece (mApproxData);
    vector<vector<double>>point(piece.solve_least_square_degree(mDegree_PW_leastsquare, Intervalle,x));
    return generate_test(point[0],point[1]);
}

double Test::testLagrangePiecewise() const
{
    Graph graph(mApproxData);
    vector<double>x(graph.make_x_points());
    PieceWiseContinuePolynomial piece (mApproxData);
    vector <vector<double>> approx(piece.solve_lagrange_degree(Intervalle, x));
    return generate_test(approx[0],approx[1]);
}

bool Test::CompareDoubles2 (double const& A, double const& B) const
{
    double const EPSILON = 0.2;
    double diff (A - B);
    return (diff < EPSILON) && (-diff < EPSILON);
}

double Test::generate_test(vector<double> const& x,vector<double> const& y) const
{
    //GENERATE THE CONTROL VALUES
    vector<double> controlY;
    for (auto const& element : x)
    {
        controlY.push_back(cos(M_PI*element));
    }

    ///Plot///
    Gnuplot g1 = Gnuplot("lines");
    g1.set_style("points");
    g1.plot_xy(x, y, "Approximation");
    sleep(2);
    g1.plot_xy(x, controlY, "Default points");
    sleep(5);

    size_t counter(0);

    for (size_t i(0); i < controlY.size(); i++) {
        if (CompareDoubles2(y[i], controlY[i])) {
            counter++;
        }
    }

    double counterDouble(counter);

    return counterDouble / x.size();
}