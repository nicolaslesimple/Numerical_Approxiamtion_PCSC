/**
 * \class FFTreal
 *
 * \ingroup PackageName
 * (Note, this needs exactly one \defgroup somewhere)
 *
 * \brief This is the function to call to perform the FFT of a given set of values but also to implement the data
 * approximation by computing the fourier series coefficients.
 *
 *
 * \note Optional part of the project
 *
 * \author (last to touch it) $Author: DC $
 *
 * \version $Revision: 1.0 $
 *
 * \date $Date: 2017.12.09 $
 *
 * Contact: david.cleres@epfl.ch & nicolas.lesimple@epfl.ch
 *
 */

#ifndef PCSC2017_GROUP5_FFTREAL_H
#define PCSC2017_GROUP5_FFTREAL_H

#include <vector>

///@class
class FFTreal {

public:

    /** \brief Computes the discrete Fourier transform (DFT) of the given complex vector, storing the result back into the vector.
     * The vector can have any length. This is a wrapper function.
     * \param real is a vector with the values read from the data.dat file
     * \param imag is a vector with the values read from the data.dat file, if we have only real entries then you have to
     * specify a vector with the same size as real but filled with zeros.
     */
    void transform(std::vector<double> &real, std::vector<double> &imag);

    /** \brief Computes the inverse discrete Fourier transform (IDFT) of the given complex vector, storing the result back into the vector.
     * The vector can have any length. This is a wrapper function. This transform does not perform scaling, so the inverse is not a true inverse.
     * \param real is a vector with the values read from the data.dat file
     * \param imag is a vector with the values read from the data.dat file, if we have only real entries then you have to
     * specify a vector with the same size as real but filled with zeros.
     */
    void inverseTransform(std::vector<double> &real, std::vector<double> &imag);

    /** \brief Computes the discrete Fourier transform (DFT) of the given complex vector, storing the result back into the vector.
     * The vector's length must be a power of 2. Uses the Cooley-Tukey decimation-in-time radix-2 algorithm.
     * \param real is a vector with the values read from the data.dat file
     * \param imag is a vector with the values read from the data.dat file, if we have only real entries then you have to
     * specify a vector with the same size as real but filled with zeros.
     */
    void transformRadix2(std::vector<double> &real, std::vector<double> &imag);

    /** \brief Computes the discrete Fourier transform (DFT) of the given complex vector, storing the result back into the vector.
     * The vector can have any length. This requires the convolution function, which in turn requires the radix-2 FFT function.
     * Uses Bluestein's chirp z-transform algorithm.
     * \param real is a vector with the values read from the data.dat file
     * \param imag is a vector with the values read from the data.dat file, if we have only real entries then you have to
     * specify a vector with the same size as real but filled with zeros.
     */
    void transformBluestein(std::vector<double> &real, std::vector<double> &imag);

    /** \brief Computes the circular convolution of the given real vectors. Each vector's length must be the same
     * \param x is a vector with the values of the left element to convolve
     * \param y is a vector with the values of the right element to convolve
     */
    void convolve(const std::vector<double> &x, const std::vector<double> &y, std::vector<double> &out);

    /** \brief Computes the circular convolution of the given complex vectors. Each vector's length must be the same.
     * \param xreal is a vector with the values read from the data.dat file
     * \param xreal is a vector with the values read from the data.dat file
     * \param ximag is a vector with the values read from the data.dat file
     * \param yimag is a vector with the values read from the data.dat file, if we have only real entries then you have to
     */
    void convolve(
            const std::vector<double> &xreal, const std::vector<double> &ximag,
            const std::vector<double> &yreal, const std::vector<double> &yimag,
            std::vector<double> &outreal, std::vector<double> &outimag);

    /** \brief Computes the fourier coefficients.
     * \param real is a vector with the values read from the data.dat file
     * \param an is a vector with the values of the an fourier series coefficients
     * \param bn is a vector with the values of the bn fourier series coefficients
     * \param period represents the period of the chosen periodic funtion
     */
   void transformCoefs(const std::vector<double> &real, std::vector<double> &an, std::vector<double> &bn,
                       const size_t &period);

    /** \brief Computes the fourier series based on the coeficents calculated in the transformCoef method.
    * \param real is a vector with the values read from the data.dat file
    * \param an is a vector with the values of the an fourier series coefficients
    * \param bn is a vector with the values of the bn fourier series coefficients
    * \param period represents the period of the chosen periodic funtion
    * \return a vector of doubles containing the approximated data
    */
    std::vector<double> transformApproximation(std::vector<double> const& an, std::vector<double> const& bn, const size_t &period,
                                std::vector<double> &real);
};


#endif //PCSC2017_GROUP5_FFTREAL_H
