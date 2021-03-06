#include "resolution/solution.h"

long double getPathDistance(std::vector<Coordinate> &cities, std::vector<int> &path) {
    double distance = 0;
    for(int i = 0; i < path.size(); i++) {
        Coordinate a = cities.at(path.at(i));
        Coordinate b = cities.at( (i + 1 < path.size()) ? path.at(i + 1) : path.at(0));
        distance += std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }
    return distance;
}

long double euclidianDistance(Coordinate a, Coordinate b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}
