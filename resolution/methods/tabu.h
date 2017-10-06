#ifndef TABU_H
#define TABU_H

#include "resolution/solution.h"
#include <vector>

using Tabu = std::pair<int, int>;

bool hasTabuConfig(Tabu tabus[], std::vector<int> path, int tabuLength) {
    for(int i = 0; i < path.size(); i++) {
        int source = path.at(i);
        int target = path.at((i + 1) % path.size());
        for(int j = 0; j < tabuLength; j++) {
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

Tabu newTabu(int source, int target, std::vector<int> &path) {
    if(source < 0)
        source = path.size() - 1;
    if(source == path.size())
        source = 0;
    if(target < 0)
        target = path.size() - 1;
    if(target == path.size())
        target = 0;
    Tabu tabu;
    tabu.first = path.at(source);
    tabu.second = path.at(target);
    return tabu;
}

Solution tabuSearch(std::vector<Coordinate> &coordinates,
                    Solution &sol,
                    std::function<void(const Solution&)> setSolution = nullptr,
                    std::function<void(std::string)> log = nullptr,
                    std::function<void(double)> chartLog = nullptr,
                    std::function<void(std::string)> logIterations = nullptr,
                    std::function<bool()> stopRequested = nullptr,
                    int tabuLength = 5,
                    int itMax = 1000) {
    Tabu tabus[tabuLength];
    Solution bestSol = sol;
    Solution currentSol = sol;
    auto start = std::chrono::steady_clock::now();
    log("Iniciado");

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
                if(tmp < tabuDistance && !configAlreadyExists(tabus, newTabu(i - 1, i, neighbor.path), tabuLength)) {
                    tabuDistance = tmp;
                    tabuSource = i - 1;
                    tabuTarget = i;
                }
                tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, i),
                    getCoordinate(coordinates, neighbor.path, i + 1)
                );
                neighbor.distance += tmp;
                if(tmp < tabuDistance && !configAlreadyExists(tabus, newTabu(i, i + 1, neighbor.path), tabuLength)) {
                    tabuDistance = tmp;
                    tabuSource = i;
                    tabuTarget = i + 1;
                }
                tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, j - 1),
                    getCoordinate(coordinates, neighbor.path, j)
                );
                neighbor.distance += tmp;
                if(tmp < tabuDistance && !configAlreadyExists(tabus, newTabu(j - 1, j, neighbor.path), tabuLength)) {
                    tabuDistance = tmp;
                    tabuSource = j - 1;
                    tabuTarget = j;
                }
                tmp = euclidianDistance(
                    getCoordinate(coordinates, neighbor.path, j),
                    getCoordinate(coordinates, neighbor.path, j + 1)
                );
                neighbor.distance += tmp;
                if(tmp < tabuDistance && !configAlreadyExists(tabus, newTabu(j, j + 1, neighbor.path), tabuLength)) {
                    tabuDistance = tmp;
                    tabuSource = j;
                    tabuTarget = j + 1;
                }
                if(hasTabuConfig(tabus, neighbor.path, tabuLength)) {
                    continue;
                }
                if(neighbor.distance < nextSol.distance) {
                    nextSol = neighbor;
                }
                if(neighbor.distance < bestSol.distance) {
                    bestSol = neighbor;
                    auto now = std::chrono::steady_clock::now();
                    double seconds = std::chrono::duration<double>(now-start).count();
                    log( "[ "+ std::to_string(seconds) +" segundos ] Distância melhorada: " + std::to_string(currentSol.distance) );
                }
            }
        }
        Tabu tabu = newTabu(tabuSource, tabuTarget, nextSol.path);
        tabus[it % tabuLength] = tabu;

        currentSol = nextSol;

        setSolution( currentSol );
        chartLog( currentSol.distance );

        it++;
    } while(!stopRequested()/*it < itMax*/);
    return bestSol;
}

Solution tabuSearch(std::vector<Coordinate> &coordinates,
                    std::function<void(const Solution&)> setSolution = nullptr,
                    std::function<void(std::string)> log = nullptr,
                    std::function<void(double)> chartLog = nullptr,
                    std::function<void(std::string)> logIterations = nullptr,
                    std::function<bool()> stopRequested = nullptr,
                    int tabuLength = 5,
                    int itMax = 1000) {
    Solution sol;
    for(int i = 0; i < coordinates.size(); i++) {
        sol.path.push_back(i);
    }
    std::random_shuffle(sol.path.begin(), sol.path.end());
    sol.distance = getPathDistance(coordinates, sol.path);
    return tabuSearch(coordinates, sol, setSolution, log, chartLog, logIterations, stopRequested, tabuLength, itMax);
}

#endif // TABU_H
