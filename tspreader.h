#ifndef TSPREADER_H
#define TSPREADER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <stdlib.h>
#include "solution.h"

#include "solution.h"

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::vector<Coordinate> getTspInstance(std::string filePath, int numberOfCoordinates = INT_MAX) {

    std::ifstream file(filePath);
    std::string line;
    do {
        std::getline(file, line);
    } while ( line != "NODE_COORD_SECTION" );

    std::vector<Coordinate> coordinates;
    for(int i = 0; i < numberOfCoordinates; i++) {
        std::getline(file, line);
        if( i == numberOfCoordinates || line == "EOF")
            break;
        std::vector<std::string> points = split(line, ' ');
        double x = std::stod(points.at(1));
        double y = std::stod(points.at(2));
        coordinates.push_back(Coordinate(x, y));
    }
    return coordinates;
}

#endif // TSPREADER_H
