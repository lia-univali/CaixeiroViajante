#ifndef ITERATEDSEARCH_H
#define ITERATEDSEARCH_H

struct Solution {
    std::vector<int> path;
    long double distance = INT_MAX;
};

long double getPathDistance(std::vector<Coordinate> &cities, std::vector<int> &path) {
    double distance = 0;
    for(int i = 0; i < path.size(); i++) {
        Coordinate a = cities.at(path.at(i));
        Coordinate b = cities.at( (i + 1 < path.size()) ? path.at(i + 1) : path.at(0));
        distance += std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }
    return distance;
}

Solution iteratedSearch(std::vector<Coordinate> cities, int startNode) {
    Solution currentSol;
    currentSol.path.push_back(startCity);
    for(int i = 0; i < cities.size(); i++)
        if(i != startCity)
            currentSol.path.push_back(i);

    Solution bestSol;
    bool stoppingCriterion = false;
    do {
        if(currentSol.distance < bestSol.distance) {
            bestSol = currentSol;
        }
    } while(!stoppingCriterion);
}

#endif // ITERATEDSEARCH_H
