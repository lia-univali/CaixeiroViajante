#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "graph.h"
#include "solution.h"
#include <vector>
#include <algorithm>

Solution bruteForceSearch(Graph &graph, std::string &startNode) {
    std::vector<int> currentPath;
    // preenche o caminho a partir do vértice inicial
    int numberOfNodes = graph.vertices.size();
    for(int i = graph.getIndexOfVertice(startNode); currentPath.size() != numberOfNodes; i++)
        currentPath.push_back((i > numberOfNodes) ? numberOfNodes % i : i);

    Solution sol;
    float currentWeight;
    do {
        currentWeight = getPathWeight(currentPath, graph);
        if(currentWeight != -1 && sol.weight > currentWeight) {
            sol.weight = currentWeight;
            sol.path = currentPath;
        }
    } while(std::next_permutation(currentPath.begin() + 1, currentPath.end()));
    return sol;
}

#endif
