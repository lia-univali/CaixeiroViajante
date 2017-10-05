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

void printPath(std::vector<int> path) {
    std::cout << "[ ";
    for(int i = 0; i < path.size(); i++) {
        std::cout << path.at(i) << " ";
    }
    std::cout << "]" << std::endl;
}

bool alreadyExists(const std::set<Solution> &solSet, Solution sol) {
    for(const Solution &current : solSet) {
        if(current == sol) {
            return true;
        }
    }
    return false;
}

double getMinDistance(std::vector<Coordinate> &coordinates, std::vector<int> &path) {
    double minDist = euclidianDistance(
        getCoordinate(coordinates, path, path.size() - 1),
        getCoordinate(coordinates, path, 0)
    );
    for(int i = 0; i < path.size() - 1; i++) {
        double dist = euclidianDistance(
            getCoordinate(coordinates, path, i),
            getCoordinate(coordinates, path, i + 1)
        );
        if(dist < minDist) {
            minDist = dist;
        }
    }
    return minDist;
}

Solution aStar(std::vector<Coordinate> &coordinates, Solution &sol, int maxIt) {
    int numberOfCities = sol.path.size();

    Solution currentSol = sol;
    double currentSolMinDistance = getMinDistance(coordinates, sol.path);
    double currentSolDistance = sol.distance;
    currentSol.distance = currentSolMinDistance + sol.distance / numberOfCities;

    Solution bestSol = currentSol;

    std::set<Solution> openSet, closedSet;
    closedSet.insert(currentSol);

    int it = 0;
    do {
        for(int i = 0; i < currentSol.path.size(); i++) {
            for(int j = i + 1; j < currentSol.path.size(); j++) {
                double outI, outJ, inIa, inIb, inJa, inJb;
                double neighborMinDist = currentSolMinDistance;
                if(i + 1 == j) {
                    outI = euclidianDistance(
                        getCoordinate(coordinates, currentSol.path, i - 1),
                        getCoordinate(coordinates, currentSol.path, i)
                    );
                    outJ = euclidianDistance(
                        getCoordinate(coordinates, currentSol.path, j),
                        getCoordinate(coordinates, currentSol.path, j + 1)
                    );
                } else if(i == 0 && j + 1 == currentSol.path.size()) {
                    outJ = euclidianDistance(
                        getCoordinate(coordinates, currentSol.path, j - 1),
                        getCoordinate(coordinates, currentSol.path, j)
                    );
                    outI = euclidianDistance(
                        getCoordinate(coordinates, currentSol.path, i),
                        getCoordinate(coordinates, currentSol.path, i + 1)
                    );
                } else {
                    outI = getDistanceBetween(
                        getCoordinate(coordinates, currentSol.path, i - 1),
                        getCoordinate(coordinates, currentSol.path, i),
                        getCoordinate(coordinates, currentSol.path, i + 1)
                    );
                    outJ = getDistanceBetween(
                        getCoordinate(coordinates, currentSol.path, j - 1),
                        getCoordinate(coordinates, currentSol.path, j),
                        getCoordinate(coordinates, currentSol.path, j + 1)
                    );
                }
                inIa = euclidianDistance(getCoordinate(coordinates, currentSol.path, j - 1),
                                                 getCoordinate(coordinates, currentSol.path, i));
                inIb = euclidianDistance(getCoordinate(coordinates, currentSol.path, i),
                                                 getCoordinate(coordinates, currentSol.path, j + 1));

                inJa = euclidianDistance(getCoordinate(coordinates, currentSol.path, i - 1),
                                                 getCoordinate(coordinates, currentSol.path, j));
                inJb = euclidianDistance(getCoordinate(coordinates, currentSol.path, j),
                                                 getCoordinate(coordinates, currentSol.path, i + 1));
                if(inIa > 0 && inIa < neighborMinDist) {
                    neighborMinDist = inIa;
                } else if (inIb > 0 && inIb < neighborMinDist) {
                    neighborMinDist = inIb;
                } else if (inJa > 0 && inJa < neighborMinDist) {
                    neighborMinDist = inJa;
                } else if (inJb > 0 && inJb < neighborMinDist) {
                    neighborMinDist = inJb;
                }

                Solution neighbor;
                neighbor.path = currentSol.path;
                neighbor.distance = neighborMinDist + (currentSolDistance - (outI + outJ) + (inIa + inIb + inJa + inJb)) / numberOfCities;
                std::swap(neighbor.path.at(i), neighbor.path.at(j));

                if(!alreadyExists(closedSet, neighbor) && !alreadyExists(openSet, neighbor)) {
                    openSet.insert(neighbor);
                }
                if(neighbor.distance < bestSol.distance) {
                    bestSol = neighbor;
                }
            }
        }
        currentSol = *openSet.begin();
        openSet.erase(openSet.begin());
        closedSet.insert(currentSol);
        currentSolMinDistance = getMinDistance(coordinates, currentSol.path);
        currentSolDistance = (currentSol.distance - currentSolMinDistance) * numberOfCities;

        system("CLS");
        std::cout << "Closed Set: " << closedSet.size() << std::endl;
        std::cout << "Open Set: " << openSet.size() << std::endl;
    } while(++it < maxIt && !openSet.empty());
    bestSol.distance = getPathDistance(coordinates, bestSol.path);
    return bestSol;
}

Solution aStar(std::vector<Coordinate> coordinates, int maxIt) {
    Solution sol;
    for(int i = 0; i < coordinates.size(); i++)
        sol.path.push_back(i);
    std::random_shuffle(sol.path.begin(), sol.path.end());
    sol.distance = getPathDistance(coordinates, sol.path);
    return aStar(coordinates, sol, maxIt);
}

#endif // TABU_H
