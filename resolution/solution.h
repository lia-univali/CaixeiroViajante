#ifndef SOLUTION_H
#define SOLUTION_H

#include <limits.h>
#include <cmath>
#include <string>
#include <vector>

struct Coordinate {
    std::string name;
    float x, y;
    Coordinate();
    Coordinate(float x, float y)
        : x (x), y (y) {}
};

struct Solution {
    std::vector<int> path;
    long double distance = INT_MAX;
};

long double getPathDistance(std::vector<Coordinate> &cities, std::vector<int> &path);

long double euclidianDistance(Coordinate a, Coordinate b);

#endif // SOLUTION_H
