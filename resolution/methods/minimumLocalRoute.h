#ifndef MINIMUMLOCALROUTE_H
#define MINIMUMLOCALROUTE_H

#include "resolution/solution.h"

Solution minimumLocalRoute(std::vector<Coordinate> &cities, int startNode,
                           std::function<void(const Solution&)> setSolution,
                           std::function<void(std::string)> log,
                           std::function<void(double)> chartLog,
                           std::function<void(std::string)> logIterations,
                           std::function<bool()> stopRequested ) {
    Solution sol;
    sol.path.push_back(startNode);
    for(int i = 0; i < cities.size(); i++) {
        if(i != startNode)
            sol.path.push_back(i);
    }
    int it = 0;
    auto start = std::chrono::steady_clock::now();
    sol.distance = getPathDistance(cities, sol.path);
    for(int i = 0; i < sol.path.size() - 1 && !stopRequested(); i++) {
        double smallerDistance = euclidianDistance(
            getCoordinate(cities, sol.path, i),
            getCoordinate(cities, sol.path, i + 1)
        );
        int smallerCityIndex = i + 1;
        for(int j = i + 2; j < sol.path.size(); j++) {
            double distance = euclidianDistance(
                getCoordinate(cities, sol.path, i),
                getCoordinate(cities, sol.path, j)
            );
            if(distance < smallerDistance) {
                smallerDistance = distance;
                smallerCityIndex = j;
            }
        }
        if(smallerCityIndex == i + 1)
            continue;

        double outI, outJ, inI, inJ;
        if(i + 2 == smallerCityIndex) {
            outI = euclidianDistance(
                getCoordinate(cities, sol.path, i),
                getCoordinate(cities, sol.path, i + 1)
            );
            outJ = euclidianDistance(
                getCoordinate(cities, sol.path, smallerCityIndex),
                getCoordinate(cities, sol.path, smallerCityIndex + 1)
            );
        } else {
            outI = getDistanceBetween(
                getCoordinate(cities, sol.path, i),
                getCoordinate(cities, sol.path, i + 1),
                getCoordinate(cities, sol.path, i + 2)
            );
            outJ = getDistanceBetween(
                getCoordinate(cities, sol.path, smallerCityIndex - 1),
                getCoordinate(cities, sol.path, smallerCityIndex),
                getCoordinate(cities, sol.path, smallerCityIndex + 1)
            );
        }
        inI = getDistanceBetween(
            getCoordinate(cities, sol.path, smallerCityIndex - 1),
            getCoordinate(cities, sol.path, i + 1),
            getCoordinate(cities, sol.path, smallerCityIndex + 1)
        );
        inJ = getDistanceBetween(
            getCoordinate(cities, sol.path, i),
            getCoordinate(cities, sol.path, smallerCityIndex),
            getCoordinate(cities, sol.path, i + 2)
        );
        sol.distance = sol.distance - (outI + outJ) + (inI + inJ);
        std::swap(sol.path.at(i + 1), sol.path.at(smallerCityIndex));

        auto now = std::chrono::steady_clock::now();
        double seconds = std::chrono::duration<double>(now-start).count();
        log( "[ "+ std::to_string(seconds) +" segundos ] Distância construída: " + std::to_string(sol.distance) );
        chartLog( sol.distance );
        setSolution( sol );
        it++;
        logIterations( std::to_string(it) );
    }
    log( "Distância final: " + std::to_string(sol.distance) );
    return sol;
}

#endif // MINIMUMLOCALROUTE_H
