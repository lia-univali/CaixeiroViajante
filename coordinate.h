#ifndef COORDINATE
#define COORDINATE

struct Coordinate {
    std::string name;
    float x, y;
    Coordinate(){}
    Coordinate(float x, float y)
        : x (x), y (y) {}
};


#endif // COORDINATE

