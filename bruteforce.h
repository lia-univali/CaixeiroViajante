#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "graph.h"
#include "tspreader.h"
#include <vector>
#include <algorithm>
#include <math.h>

struct Solution {
    std::vector<int> path;
    long double distance = INT_MAX;
};

long double getPathDistance(std::vector<Coordinate> &cities, std::vector<int> &path) {
    double distance = 0;
    for(int i = 0; i < path.size(); i++) {
        Coordinate a = cities.at(path.at(i));
        Coordinate b = cities.at( (i + 1 < path.size()) ? path.at(i + 1) : path.at(0));
        distance += std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }
    return distance;
}

Solution bruteForceSearch(std::vector<Coordinate> &cities, int startCity) {
    Solution currentSol;
    currentSol.path.push_back(startCity);
    for(int i = 0; i < cities.size(); i++)
        if(i != startCity)
            currentSol.path.push_back(i);

    Solution bestSol;
    do {
        currentSol.distance = getPathDistance(cities, currentSol.path);
//        std::cout << bestSol.distance << " " << currentSol.distance << std::endl;
        if(currentSol.distance < bestSol.distance) {
            bestSol = currentSol;
            std::cout << "[";
            for(int i = 0; i < currentSol.path.size(); i++)
                std::cout << " " << currentSol.path.at(i) << " ";
            std::cout << "]" << " Distance: " << currentSol.distance << std::endl;
        }

    } while(std::next_permutation(currentSol.path.begin() + 1, currentSol.path.end()));
    return bestSol;
}

#endif
