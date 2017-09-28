#ifndef MINIMUMLOCALROUTE_H
#define MINIMUMLOCALROUTE_H

#include "solution.h"

Solution minimumLocalRoute(std::vector<Coordinate> &cities, int startNode) {
    Solution sol;
    sol.path.push_back(startNode);
    sol.distance = 0;

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
    } while(closedSet.size() > 0);
    Coordinate source = cities.at(sol.path.back());
    Coordinate target = cities.at(startNode);
    sol.distance += euclidianDistance(source, target);
    return sol;
}

#endif // MINIMUMLOCALROUTE_H
