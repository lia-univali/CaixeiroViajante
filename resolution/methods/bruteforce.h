#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "resolution/solution.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <thread>

Solution bruteForceSearch(std::vector<Coordinate> &cities, int startCity,
                          std::function<void(const Solution&)> setSolution,
                          std::function<void(std::string)> log,
                          std::function<void(double)> chartLog,
                          std::function<bool()> stopRequested ) {
    Solution currentSol;
    currentSol.path.push_back(startCity);
    for(size_t i = 0; i < cities.size(); i++)
        if(i != startCity)
            currentSol.path.push_back(i);

    Solution bestSol;
    auto start = std::chrono::steady_clock::now();
    do {
        currentSol.distance = getPathDistance(cities, currentSol.path);

        if(currentSol.distance < bestSol.distance) {
            bestSol = currentSol;
            auto now = std::chrono::steady_clock::now();
            double seconds = std::chrono::duration<double>(now-start).count();
            log( "[ "+ std::to_string(seconds) +" segundos ] Distância melhorada: " + std::to_string(currentSol.distance) );
        }

        setSolution( currentSol );
        chartLog( currentSol.distance );
    } while( std::next_permutation(currentSol.path.begin() + 1, currentSol.path.end()) && !stopRequested() );
    log( "Melhor distância encontrada: " + std::to_string(bestSol.distance) );
    return bestSol;
}

#endif
