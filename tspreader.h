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

#include <iostream>
std::vector<Coordinate> getTspInstance(std::string filePath, int numberOfCoordinates = INT_MAX) {

    printf("Opening\n");
    std::ifstream file(filePath);
    std::string line;
    do {
        std::getline(file, line);
        std::cout << "line [" << line.compare("NODE_COORD_SECTION") << "]: '" << line << "'" << std::endl;
        std::getchar();
    } while(line.compare("NODE_COORD_SECTION") != 0);

    printf("Started\n");
    std::vector<Coordinate> coordinates;
    for(int i = 0; i < numberOfCoordinates; i++) {
        printf("Loading %d\n",i);
        std::getline(file, line);
        if(numberOfCoordinates == INT_MAX || line == "EOF")
            break;
        std::vector<std::string> points = split(line, ' ');
        double x = std::stod(points.at(1));
        double y = std::stod(points.at(2));
        coordinates.push_back(Coordinate(x, y));
    }
    return coordinates;
}

#endif // TSPREADER_H
