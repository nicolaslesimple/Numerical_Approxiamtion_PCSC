/**
* A C++ interface to gnuplot.
*
* @brief This is a direct translation from the C interface
* written by N. Devillard (which is available from
* http://ndevilla.free.fr/gnuplot/). As in the C interface
* this uses pipes and so wont run on a system that doesn't
* have POSIX pipe support.
*
* Rajarshi Guha
*
 *
 * Improvements and optimizations have been added by:
 * David Cleres & Nicolas Lesimple
*
* 07/03/03
*
* \file gnuplot_i.cpp
*
*/

#ifndef _GNUPLOT_PIPES_H_
#define _GNUPLOT_PIPES_H_

#include <stdarg.h>
#include <unistd.h>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <stdexcept>

#define GP_MAX_TMP_FILES    64
#define GP_TMP_NAME_SIZE    512
#define GP_CMD_SIZE         1024
#define GP_TITLE_SIZE       80

using namespace std;

///@class
class GnuplotException : public runtime_error
{
    public:
        GnuplotException(const string &msg) : runtime_error(msg){}
};

///@class
class Gnuplot
{
    private:
        FILE            *gnucmd;
        string           pstyle;
        vector<string>   to_delete;
        int              nplots;
        bool             get_program_path(const string);
        bool             valid;
    public:

        ///Default Constructor
        Gnuplot();

        /// set a style during construction
        Gnuplot(const string &);
        
        /// @brief The equivilant of gnuplot_plot_once, the two forms
        /// allow you to plot either (x,y) pairs or just a single
        /// vector at one go
        ///@param title is the title of the graph
        ///@param style is the style of the graph
        ///@param xlabel is the name of the x axis of the graph
        ///@param ylabel is the name of the y axis of the graph
        Gnuplot(const string &, // title
                const string &, // style
                const string &, // xlabel
                const string &, // ylabel
                vector<double> const& , vector<double> const&);

        /// @brief The equivilant of gnuplot_plot_once, the two forms
        /// allow you to plot either (x,y) pairs or just a single
        /// vector at one go
        ///@param title is the title of the graph
        ///@param style is the style of the graph
        ///@param xlabel is the name of the x axis of the graph
        ///@param ylabel is the name of the y axis of the graph
        Gnuplot(const string &, //title
                const string &, //style
                const string &, //xlabel
                const string &, //ylabel
                vector<double> const&);

        ///@brief destructor
        ~Gnuplot();

        /// @brief send a command to gnuplot
        void cmd(const char*, ...);

        /// @brief set line style
        void set_style(const string &);

        /// @brief set y axis labels
        void set_ylabel(const string &);

        /// @brief set x axis labels
        void set_xlabel(const string &);

        /// @brief plot a single vector
        void plot_x(vector<double>, 
                const string & // title
                );

        /// @brief plot x,y pairs
        void plot_xy(vector<double>, vector<double>, 
                const string  & // title
                );

        /// @brief plot an equation of the form: y = ax + b. You supply a and b
        void plot_slope(
                double, // a
                double, // b 
                const string & // title
                );

        /// @brief plot an equation supplied as a string
        void plot_equation(
                const string &, // equation 
                const string &  // title
                );

        /// @brief if multiple plots are present it will clear the plot area
        void reset_plot(void);

        /// @brief assess the validity
        bool is_valid(void);
};

#endif
