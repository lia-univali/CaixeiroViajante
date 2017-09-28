#ifndef MINIMUMLOCALROUTE_H
#define MINIMUMLOCALROUTE_H

long double euclidianDistance(Coordinate a, Coordinate b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

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

//    Solution currentSol;
//    currentSol.path.push_back(startCity);
//    for(int i = 0; i < cities.size(); i++)
//        if(i != startCity)
//            currentSol.path.push_back(i);
//    Solution bestSol;
//    bool stoppingCriterion = false;
//    do {
//        bool improvement = false;
//        if(currentSol.distance < bestSol.distance) {
//            bestSol = currentSol;
//            improvement = true;
//        }
//        if(!improvement) {
//
//        }
//    } while(!stoppingCriterion);
}

#endif // MINIMUMLOCALROUTE_H
