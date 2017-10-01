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

std::vector<Coordinate> getTspInstance(
        std::string filePath,
        std::map<std::string,std::string> &metadata,
        int numberOfCoordinates = INT_MAX
    ){
    {
        size_t pos = filePath.find_last_of('/') +1;
        metadata["arquivo"] = filePath.substr(pos);
    }

    std::ifstream file(filePath);
    std::string line;
    do {
        std::getline(file, line);
        if (line.substr(0,9) == "DIMENSION"){
            std::string sub = line.substr( line.find_last_of(':')+1 );
            while (sub.front() == ' ') sub = sub.substr(1);
            while (sub.back()  == ' ') sub = sub.substr(0,sub.size()-1);
            metadata["pontos"] = sub;
        }
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
