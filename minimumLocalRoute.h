#ifndef MINIMUMLOCALROUTE_H
#define MINIMUMLOCALROUTE_H

#include "solution.h"

Solution minimumLocalRoute(std::vector<Coordinate> &cities, int startNode,
                           std::function<void(const Solution&)> setSolution,
                           std::function<void(std::string)> log,
                           std::function<void(double)> chartLog,
                           std::function<bool()> stopRequested ) {
    Solution sol;
    sol.path.push_back(startNode);

    std::vector<int> closedSet;
    for(int i = 0; i < cities.size(); i++) {
        if(i != startNode)
            sol.path.push_back(i);
    }
    auto start = std::chrono::steady_clock::now();
    sol.distance = getPathDistance(cities, sol.path);
    for(int i = 1; i < sol.path.size() && !stopRequested(); i++) {
        Coordinate source = cities.at(sol.path.at(i));
        double smallerDistance = INT_MAX;
        int smallerCityIndex;
        for(int j = i + 1; j < sol.path.size(); j++) {
            double distance = euclidianDistance(
                getCoordinate(cities, sol.path, i),
                getCoordinate(cities, sol.path, j)
            );
            if(distance < smallerDistance) {
                smallerDistance = distance;
                smallerCityIndex = j;
            }
        }
        double outI, outJ, inI, inJ;
        if(i + 1 == smallerCityIndex) {
            outI = euclidianDistance(
                getCoordinate(cities, sol.path, i - 1),
                getCoordinate(cities, sol.path, i)
            );
            outJ = euclidianDistance(
                getCoordinate(cities, sol.path, smallerCityIndex),
                getCoordinate(cities, sol.path, smallerCityIndex + 1)
            );
        } else {
            outI = getDistanceBetween(
                getCoordinate(cities, sol.path, i - 1),
                getCoordinate(cities, sol.path, i),
                getCoordinate(cities, sol.path, i + 1)
            );
            outJ = getDistanceBetween(
                getCoordinate(cities, sol.path, smallerCityIndex - 1),
                getCoordinate(cities, sol.path, smallerCityIndex),
                getCoordinate(cities, sol.path, smallerCityIndex + 1)
            );
        }
        inI = getDistanceBetween(
            getCoordinate(cities, sol.path, smallerCityIndex - 1),
            getCoordinate(cities, sol.path, i),
            getCoordinate(cities, sol.path, smallerCityIndex + 1)
        );
        inJ = getDistanceBetween(
            getCoordinate(cities, sol.path, i - 1),
            getCoordinate(cities, sol.path, smallerCityIndex),
            getCoordinate(cities, sol.path, i + 1)
        );
        sol.distance = sol.distance - (outI + outJ) + (inI +inJ);
        std::swap(sol.path.at(i), sol.path.at(smallerCityIndex));

        auto now = std::chrono::steady_clock::now();
        double seconds = std::chrono::duration<double>(now-start).count();
        log( "[ "+ std::to_string(seconds) +" segundos ] Distância construída: " + std::to_string(sol.distance) );
        chartLog( sol.distance );
        setSolution( sol );
    }
    sol.distance -= euclidianDistance(
        getCoordinate(cities, sol.path, 0),
        getCoordinate(cities, sol.path, 1)
    );
    sol.distance -= euclidianDistance(
        getCoordinate(cities, sol.path, sol.path.size() - 2),
        getCoordinate(cities, sol.path, sol.path.size() - 1)
    );
    sol.distance += euclidianDistance(
        getCoordinate(cities, sol.path, 0),
        getCoordinate(cities, sol.path, sol.path.size() - 2)
    );
    sol.distance += euclidianDistance(
        getCoordinate(cities, sol.path, sol.path.size() - 1),
        getCoordinate(cities, sol.path, 1)
    );
    std::swap(sol.path.at(0), sol.path.back());
    log( "Distância final: " + std::to_string(sol.distance) );
    return sol;
}

#endif // MINIMUMLOCALROUTE_H
