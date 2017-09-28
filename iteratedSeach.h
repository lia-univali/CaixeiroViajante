#ifndef ITERATEDSEARCH_H
#define ITERATEDSEARCH_H

#include "solution.h"

Solution iteratedSearch(std::vector<Coordinate> cities, int startNode) {
    Solution currentSol;
    currentSol.path.push_back(startCity);
    for(int i = 0; i < cities.size(); i++)
        if(i != startCity)
            currentSol.path.push_back(i);
    Solution bestSol;
    bool stoppingCriterion = false;
    do {
        bool improvement = false;
        for(int i = 1; i < cities.size(); i++) {
            for(int j = i + 1; j < cities.size(); j++) {
                double distance = currentSol.distance;
            }
        }
        if(currentSol.distance < bestSol.distance) {
            bestSol = currentSol;
            improvement = true;
        }
        if(!improvement) {

        }
    } while(!stoppingCriterion);
}

#endif // ITERATEDSEARCH_H
