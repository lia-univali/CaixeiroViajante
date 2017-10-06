#ifndef TABU_H
#define TABU_H

#include "resolution/solution.h"
#include <vector>

using Tabu = std::pair<int, int>;

bool hasTabuConfig(Tabu tabus[], std::vector<int> path) {
    for(int i = 0; i < path.size(); i++) {
        int source = path.at(i);
        int target = path.at(i % path.size());
        for(int j = 0; j < sizeof(tabus)/sizeof(*tabus); j++) {
            if(tabus[j].first == source && tabus[j].second == target) {
//            || (tabus[j].second == source && tabus[j].first == target)) {
                return true;
            }
        }
    }
    return false;
}

bool configAlreadyExists(Tabu tabus[], Tabu tabu, int tabuLength) {
    for(int i = 0; i < tabuLength; i++) {
        if(tabus[i].first == tabu.first && tabus[i].second == tabu.second)
            return true;
//        if(tabus[i].first == tabu.second && tabus[i].second == tabu.first)
//            return true;
    }
    return false;
}

Tabu newTabu(int source, int target, int pathSize) {
    if(source < 0)
        source = pathSize - 1;
    if(source == pathSize)
        source = 0;
    if(target < 0)
        target = pathSize - 1;
    if(target == pathSize)
        target = 0;
    Tabu tabu;
    tabu.first = source;
    tabu.second = target;
    return tabu;
}

Solution tabuSearch(std::vector<Coordinate> &coordinates, Solution &sol, int itMax, int tabuLength = 5) {
    Tabu tabus[tabuLength];

    Solution bestSol = sol;
    Solution currentSol = sol;
    int it = 0;
    do {
        Solution nextSol;
        nextSol.distance = INT_MAX;
        double tabuDistance = INT_MAX;
        int tabuSource, tabuTarget;
        for(int i = 0; i < sol.path.size(); i++) {
            for(int j = i + 1; j < sol.path.size(); j++) {
                Solution neighbor = currentSol;
                neighbor.distance -= getDistanceBetween(
                    getCoordinate(coordinates, neighbor.path, i - 1),
                    getCoordinate(coordinates, neighbor.path, i),
                    getCoordinate(coordinates, neighbor.path, i + 1)
                );
                neighbor.distance -= getDistanceBetween(
                    getCoordinate(coordinates, neighbor.path, j - 1),
                    getCoordinate(coordinates, neighbor.path, j),
                    getCoordinate(coordinates, neighbor.path, j + 1)
                );
                std::swap(neighbor.path.at(i), neighbor.path.at(j));
                double tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, i - 1),
                    getCoordinate(coordinates, neighbor.path, i)
                );
                neighbor.distance += tmp;
                if(tmp < tabuDistance && !configAlreadyExists(tabus, newTabu(i - 1, i, neighbor.path.size()), tabuLength)) {
                    tabuDistance = tmp;
                    tabuSource = i - 1;
                    tabuTarget = i;
                }
                tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, i),
                    getCoordinate(coordinates, neighbor.path, i + 1)
                );
                neighbor.distance += tmp;
                if(tmp < tabuDistance && !configAlreadyExists(tabus, newTabu(i, i + 1, neighbor.path.size()), tabuLength)) {
                    tabuDistance = tmp;
                    tabuSource = i;
                    tabuTarget = i + 1;
                }
                tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, j - 1),
                    getCoordinate(coordinates, neighbor.path, j)
                );
                neighbor.distance += tmp;
                if(tmp < tabuDistance && !configAlreadyExists(tabus, newTabu(j - 1, j, neighbor.path.size()), tabuLength)) {
                    tabuDistance = tmp;
                    tabuSource = j - 1;
                    tabuTarget = j;
                }
                tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, j),
                    getCoordinate(coordinates, neighbor.path, j + 1)
                );
                neighbor.distance += tmp;
                if(tmp < tabuDistance && !configAlreadyExists(tabus, newTabu(j, j + 1, neighbor.path.size()), tabuLength)) {
                    tabuDistance = tmp;
                    tabuSource = j;
                    tabuTarget = j + 1;
                }
                if(hasTabuConfig(tabus, neighbor.path)) {
                    continue;
                }
                if(neighbor.distance < bestSol.distance) {
                    bestSol = neighbor;
                }
                if(neighbor.distance < nextSol.distance) {
                    nextSol = neighbor;
                }
            }
        }
        Tabu tabu = newTabu(tabuSource, tabuTarget, coordinates.size());
        tabus[it % tabuLength] = tabu;

        currentSol = nextSol;

//        for(int i = 0; i < tabuLength; i++) {
//            std::cout << tabus[i].first << " " << tabus[i].second << std::endl;
//        }
//        system("PAUSE");
//        system("CLS");
    } while(++it < itMax);
    return bestSol;
}

Solution tabuSearch(std::vector<Coordinate> &coordinates, int itMax, int tabuLength = 5) {
    Solution sol;
    for(int i = 0; i < coordinates.size(); i++) {
        sol.path.push_back(i);
    }
    std::random_shuffle(sol.path.begin(), sol.path.end());
    sol.distance = getPathDistance(coordinates, sol.path);
    return tabuSearch(coordinates, sol, itMax, tabuLength);
}

#endif // TABU_H
