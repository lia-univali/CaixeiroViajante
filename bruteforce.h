#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "graph.h"
#include <vector>
#include <algorithm>

struct Solution {
    std::vector<int> path;
    float weight;
    Solution() {
        weight = INT_MAX;
    }
};

float getPathWeight(int startNodeIndex, std::vector<int> path, Graph graph) {
    if(!graph.isConnected(startNodeIndex, path.at(0)))
        return -1;
    float weight = graph.getEdge(startNodeIndex, path.at(0)).distance;
    int source, target;
    for(int i = 0; i < path.size(); i++){
        source = path.at(i);
        target = (i + 1 < path.size()) ? path.at(i + 1) : startNodeIndex;
        if(graph.isConnected(source, target))
            weight += graph.getEdge(source, target).distance;
        else
            return -1; // caso não haja navegação de um trajeto entre duas cidades, ou seja, inadmissível
    }
    return weight;
}

void printPath(int startNode, std::vector<int> path) {
    std::cout << startNode;
    for(int vertice : path)
        std::cout <<  " => " << vertice;
    std::cout << std::endl;
}

Solution bruteForceSearch(Graph graph, std::string startNode) {
    int startNodeIndex = graph.getIndexOfVertice(startNode);
    // remove o vértice inicial do vetor de permutações
    std::vector<int> currentPath;
    for(int i = 0; i < graph.vertices.size(); i++)
        if(i != startNodeIndex)
            currentPath.push_back(i);
    // permuta o vetor de caminho, verificando todos caminhos possíveis
    Solution sol;
    float currentWeight;
    do {
        currentWeight = getPathWeight(startNodeIndex, currentPath, graph);
        if(currentWeight != -1 && sol.weight > currentWeight) {
            sol.weight = currentWeight;
            sol.path = currentPath;
        }
    } while(std::next_permutation(currentPath.begin(), currentPath.end()));
    return sol;
}

#endif
