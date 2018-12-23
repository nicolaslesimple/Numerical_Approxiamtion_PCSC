//
// Created by David Cleres on 27.11.17.
//

#include <stdexcept>
#include <iostream>
#include <fstream>
#include<cassert>
#include "readFile.h"

using namespace std;

void ReadFile::loadFromFile(Data& data) const
{
    std::cerr << "Reloading world from file <" << mFilename << ">" << std::endl;
    std::ifstream in (mFilename);

    assert(in.is_open());

    vector<point_t> Points;
    if (!in)
        throw std::runtime_error("Couldn't open file <" + mFilename + ">");

    while (!in.eof())
    {
        std::string bufferGender;
        double bufferWeight;
        double bufferHeight;

        in >> bufferHeight;
        in >> bufferWeight;
        data.heights.push_back(bufferHeight);
        data.weights.push_back(bufferWeight);

        point_t onePoint{};
        onePoint.x=bufferHeight;
        onePoint.y=bufferWeight;
        Points.push_back(onePoint);
    }

    if (!in.eof()) {
        throw std::runtime_error("Failed to load values from file <" + mFilename + ">");
    }
    else {
        std::cerr << "Loaded all values from file <" << mFilename << ">" << std::endl << std::flush;
    }
    in.close();
}

ReadFile::ReadFile (std::string const& filename)
    : mFilename(filename)
    {}

void ReadFile::loadFromFileTest(Data &data) const
{
    std::cerr << "Reloading world from file <" << mFilename << ">" << std::endl;
    std::ifstream in (mFilename);

    assert(in.is_open());

    vector<point_t> Points;

    if (!in)
        throw std::runtime_error("Couldn't open file <" + mFilename + ">");

    while (!in.eof())
    {
        std::string bufferGender;
        double bufferWeight;

        in >> bufferWeight;
        data.weights.push_back(bufferWeight);

        point_t onePoint{};
        onePoint.y=bufferWeight;
        Points.push_back(onePoint);
    }

    if (!in.eof()) {
        throw std::runtime_error("Failed to load values from file <" + mFilename + ">");
    }
    else {
        std::cerr << "Loaded all values from file <" << mFilename << ">" << std::endl << std::flush;
    }
    in.close();
}

std::string ReadFile::getFilename() const
{
    return mFilename;
}

void ReadFile::show(Data const& data) const
{
    for (size_t i(0); i < data.heights.size(); i++) {
        cout << "Height: " << data.heights[i] << "\t";
        cout << "Weight:" << data.weights[i] << endl;
    }
}

void ReadFile::writeFile(Data const& data) const
{
    ofstream myfile;
    myfile.open ("output.txt");

    for (size_t i(0); i < data.heights.size(); i++) {
        myfile << data.heights[i];
        myfile << data.weights[i];
    }
    myfile.close();
}

std::vector<size_t> ReadFile::loadFromFileConfig() const
{
    vector<size_t > configData;

    std::cerr << "Reloading world from file <" << mFilename << ">" << std::endl;
    std::ifstream in (mFilename);

    assert(in.is_open());

    if (!in)
        throw std::runtime_error("Couldn't open file <" + mFilename + ">");

    while (!in.eof())
    {
        string x;
        size_t bufferRegressionType, BufferChosenFunction, bufferAdditionnalData, bufferAdditionnalData2;
        in >> x >> x >> bufferRegressionType;
        in >> x >> x >> BufferChosenFunction;
        in >> x >> x >> bufferAdditionnalData;
        in >> x >> x >> bufferAdditionnalData2;

        configData.push_back(bufferRegressionType);
        configData.push_back(BufferChosenFunction);
        configData.push_back(bufferAdditionnalData);
        configData.push_back(bufferAdditionnalData2);
    }

    if (!in.eof()) {
        throw std::runtime_error("Failed to load values from file <" + mFilename + ">");
    }
    else {
        std::cerr << "Loaded all values from file <" << mFilename << ">" << std::endl << std::flush;
    }
    in.close();
    return configData;
}


