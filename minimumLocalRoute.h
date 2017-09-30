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
    sol.distance = 0;

    auto start = std::chrono::steady_clock::now();

    std::vector<int> closedSet;
    for(int i = 0; i < cities.size(); i++)
        if(i != startNode)
            closedSet.push_back(i);
    do {
        Coordinate source = cities.at(sol.path.back());
        double smallerDistance = INT_MAX;
        int closedSetIndex;
        for(int i = 0; i < closedSet.size(); i++) {
            Coordinate target = cities.at(closedSet.at(i));
            double distance = euclidianDistance(source, target);
            if(distance < smallerDistance) {
                smallerDistance = distance;
                closedSetIndex = i;

            }
        }
        sol.distance += smallerDistance;
        sol.path.push_back(closedSet.at(closedSetIndex));
        closedSet.erase(closedSet.begin() + closedSetIndex);

        auto now = std::chrono::steady_clock::now();
        double seconds = std::chrono::duration<double>(now-start).count();
        log( "[ "+ std::to_string(seconds) +" segundos ] Distância construída: " + std::to_string(sol.distance) );
        chartLog( sol.distance );
        setSolution( sol );

    } while(closedSet.size() > 0 && !stopRequested());
    Coordinate source = cities.at(sol.path.back());
    Coordinate target = cities.at(startNode);
    sol.distance += euclidianDistance(source, target);
    log( "Distância final: " + std::to_string(sol.distance) );
    return sol;
}

#endif // MINIMUMLOCALROUTE_H
