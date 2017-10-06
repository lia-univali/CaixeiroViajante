#ifndef TABU_H
#define TABU_H

#include "solution.h"
#include <vector>
#include <set>

bool operator==(const Solution &a, const Solution &b) {
    if(a.distance != b.distance)
        return false;

    if(a.path.size() != b.path.size())
        return false;

    for(int i = 0; i < a.path.size(); i++)
        if(a.path.at(i) != b.path.at(i))
            return false;

    return true;
}

bool operator<(const Solution &a, const Solution &b) {
    return a.distance <= b.distance;
}

using Tabu = std::pair<int, int>;

bool hasTabuConfig(Tabu tabus[], std::vector<int> path) {
    for(int i = 0; i < path.size(); i++) {
        int source = path.at(i);
        int target = path.at(i % path.size());
        for(int j = 0; j < sizeof(tabus); j++) {
            if((tabus[j].first == source && tabus[j].second == target)
            || (tabus[j].second == source && tabus[j].first == target)) {
                return true;
            }
        }
    }
    return false;
}

Solution tabu(std::vector<Coordinate> coordinates, int itMax) {
    int tabuLength = 10;
    Tabu tabus[tabuLength];

    Solution sol;
    for(int i = 0; i < coordinates.size(); i++) {
        sol.path.push_back(i);
    }
    std::random_shuffle(sol.path.begin(), sol.path.end());
    sol.distance = getPathDistance(coordinates, sol.path);

    Solution bestSol = sol;
    Solution currentSol = sol;
    int it = 0;
    do {
        Solution nextSol = currentSol;
        Tabu candidate;
        double highestDistance = 0;
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
                if(tmp > highestDistance) {
                    candidate.first = i - 1;
                    candidate.second = i;
                }
                tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, i),
                    getCoordinate(coordinates, neighbor.path, i + 1)
                );
                neighbor.distance += tmp;
                if(tmp > highestDistance) {
                    candidate.first = i;
                    candidate.second = i + 1;
                }
                tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, j - 1),
                    getCoordinate(coordinates, neighbor.path, j)
                );
                neighbor.distance += tmp;
                if(tmp > highestDistance) {
                    candidate.first = j - 1;
                    candidate.second = j;
                }
                tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, j),
                    getCoordinate(coordinates, neighbor.path, j + 1)
                );
                neighbor.distance += tmp;
                if(tmp > highestDistance) {
                    candidate.first = j;
                    candidate.second = j + 1;
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
        candidate.first = candidate.first % coordinates.size();
        candidate.second = candidate.second % coordinates.size();
        tabus[it % tabuLength] = candidate;
        currentSol = nextSol;
    } while(++it < itMax);
    return bestSol;
}

#endif // TABU_H
