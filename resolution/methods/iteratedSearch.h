#ifndef ITERATEDSEARCH_H
#define ITERATEDSEARCH_H

#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "resolution/solution.h"

Coordinate getCoordinate(std::vector<Coordinate> &coordinates, std::vector<int> &path, int index) {
    if(index < 0)
        index = coordinates.size() - 1;
    return coordinates.at(path.at(index % coordinates.size()));
}

double getDistanceBetween(Coordinate a, Coordinate b, Coordinate c) {
    return euclidianDistance(a, b) + euclidianDistance(b, c);
}

void randomDisturb(std::vector<int> &path, int disturbanceFactor) {
    for(int i = 0; i < disturbanceFactor; i++) {
        int a, b;
        do {
            a = rand() % path.size();
            b = rand() % path.size();
        } while(a == b);
        std::swap(path.at(a), path.at(b));
    }
}

void rouleteDisturb(std::vector<Coordinate> &coordinates, Solution &sol) {
    int totalWeight = 0;
    int index[sol.path.size()], weights[sol.path.size()];
    for(size_t i = 0; i < sol.path.size(); i++) {
        Coordinate current = getCoordinate(coordinates, sol.path, i);
        Coordinate next = getCoordinate(coordinates, sol.path, (i + 1 < sol.path.size()) ? i + 1 : 0);
        double distance = euclidianDistance(current, next);
        totalWeight += distance;

        int tmp, currentIndex = i;
        for(size_t j = 0; j < i; j++) {
            if(distance < weights[j]) {
                tmp = weights[j];
                weights[j] = distance;
                distance = tmp;
                tmp = index[j];
                index[j] = currentIndex;
                currentIndex = tmp;
            }
        }
        weights[i] = distance;
        index[i] = currentIndex;
    }
    int cut = rand() % totalWeight;
    int a, b, sum = 0;
    for(size_t i = 0; i < sol.path.size(); i++) {
        sum += weights[i];
        if(sum >= cut) {
            a = index[i];
            break;
        }
    }
    sum = 0;
    do {
        for(size_t i = 0; i < sol.path.size(); i++) {
            sum += weights[i];
            if(sum >= cut) {
                b = index[i];
                break;
            }
        }
    } while(a != b);
    std::swap(sol.path.at(a), sol.path.at(b));
}

#include <mutex>

Solution iteratedSearch(std::vector<Coordinate> &cities, std::vector<int> startPath, int maxIt, int disturbanceFactor = 2,
                        std::function<void(const Solution&)> setSolution = nullptr,
                        std::function<void(std::string)> log = nullptr,
                        std::function<void(double)> chartLog = nullptr,
                        std::function<void(std::string)> logIterations = nullptr,
                        std::function<bool()> stopRequested = nullptr ) {
    auto start = std::chrono::steady_clock::now();

    log("Iniciado");
    srand(time(NULL));
    Solution currentSol;
    currentSol.path = startPath;
    currentSol.distance = getPathDistance(cities, currentSol.path);
    Solution bestGlobalSol = currentSol;
    Solution bestLocalSol = currentSol;
    int it = 0;
    std::mutex mut;
    bool disturbing = false;
    do {
        std::vector<int> currentPath = currentSol.path;
        double currentDistance = currentSol.distance;

        Solution bestNeighbor = currentSol;
        #pragma omp parallel for
        for(size_t i = 0; i < currentPath.size(); i++) {
            for(size_t j = i + 1; j < currentPath.size(); j++) {
                double outI, outJ, inI, inJ;
                if(i + 1 == j) {
                    outI = euclidianDistance(
                        getCoordinate(cities, currentPath, i - 1),
                        getCoordinate(cities, currentPath, i)
                    );
                    outJ = euclidianDistance(
                        getCoordinate(cities, currentPath, j),
                        getCoordinate(cities, currentPath, j + 1)
                    );
                } else if(i == 0 && j + 1 == currentPath.size()) {
                    outI = euclidianDistance(
                        getCoordinate(cities, currentPath, i),
                        getCoordinate(cities, currentPath, i + 1)
                    );
                    outJ = euclidianDistance(
                        getCoordinate(cities, currentPath, j - 1),
                        getCoordinate(cities, currentPath, j)
                    );
                } else {
                    outI = getDistanceBetween(
                        getCoordinate(cities, currentPath, i - 1),
                        getCoordinate(cities, currentPath, i),
                        getCoordinate(cities, currentPath, i + 1)
                    );
                    outJ = getDistanceBetween(
                        getCoordinate(cities, currentPath, j - 1),
                        getCoordinate(cities, currentPath, j),
                        getCoordinate(cities, currentPath, j + 1)
                    );
                }
                inI = getDistanceBetween(
                    getCoordinate(cities, currentPath, j - 1),
                    getCoordinate(cities, currentPath, i),
                    getCoordinate(cities, currentPath, j + 1)
                );
                inJ = getDistanceBetween(
                    getCoordinate(cities, currentPath, i - 1),
                    getCoordinate(cities, currentPath, j),
                    getCoordinate(cities, currentPath, i + 1)
                );
                Solution neighbor;
                neighbor.path = currentPath;
                neighbor.distance = currentDistance - (outI + outJ) + (inI + inJ);
                std::swap(neighbor.path.at(i), neighbor.path.at(j));
                if (neighbor.distance < currentSol.distance){
                    mut.lock();
                    if(neighbor.distance < bestNeighbor.distance) {
                        bestNeighbor = neighbor;
                    }
                    mut.unlock();
                }
            }
        }
        currentSol = bestNeighbor;

        if(currentSol.distance < bestLocalSol.distance) {
            bestLocalSol = currentSol;
            if(bestLocalSol.distance < bestGlobalSol.distance) {
                bestGlobalSol = bestLocalSol;
                auto now = std::chrono::steady_clock::now();
                double seconds = std::chrono::duration<double>(now-start).count();
                log( "[ "+ std::to_string(seconds) +" segundos ] Distância melhorada: " + std::to_string(currentSol.distance) );
                disturbing = false;
            }
        } else {
            /*if ( it >= maxIt ){
                break;
            }*/
            randomDisturb(bestLocalSol.path, disturbanceFactor);
            bestLocalSol.distance = getPathDistance(cities, bestLocalSol.path);
            currentSol = bestLocalSol;
            if(!disturbing) {
                log( "Recalculando rota aletoriamente..." );
                disturbing = true;
            }
//            rouleteDisturb(cities, bestSol);
        }

        setSolution( currentSol );
        chartLog( currentSol.distance );

        it++;
        logIterations( std::to_string(it) );
    } while (/* it < maxIt && */!stopRequested() );
    log( "Melhor distância encontrada: " + std::to_string(bestGlobalSol.distance) );
    return bestGlobalSol;
}

Solution iteratedSearch(std::vector<Coordinate> &coordinates, int maxIt, int disturbanceFactor = 2,
                        std::function<void(const Solution&)> setSolution = nullptr,
                        std::function<void(std::string)> log = nullptr,
                        std::function<void(double)> chartLog = nullptr,
                        std::function<void(std::string)> logIterations = nullptr,
                        std::function<bool()> stopRequested = nullptr
                ) {
    std::vector<int> path;
    for(size_t i = 0; i < coordinates.size(); i++)
        path.push_back(i);
    std::random_shuffle( path.begin(), path.end() );
    return iteratedSearch(coordinates, path, maxIt, disturbanceFactor, setSolution, log, chartLog, logIterations, stopRequested );
}

#endif // ITERATEDSEARCH_H
