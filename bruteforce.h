#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "graph.h"
#include "tspreader.h"
#include "solution.h"
#include <vector>
#include <algorithm>
#include <math.h>

Solution bruteForceSearch(std::vector<Coordinate> &cities, int startCity) {
    Solution currentSol;
    currentSol.path.push_back(startCity);
    for(int i = 0; i < cities.size(); i++)
        if(i != startCity)
            currentSol.path.push_back(i);

    Solution bestSol;
    do {
        currentSol.distance = getPathDistance(cities, currentSol.path);
        if(currentSol.distance < bestSol.distance) {
            bestSol = currentSol;
        }

    } while(std::next_permutation(currentSol.path.begin() + 1, currentSol.path.end()));
    return bestSol;
}

#endif
