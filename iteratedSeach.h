#ifndef ITERATED_SEARCH_H
#define #ITERATED_SEARCH_H

#include "graph.h"
#include "solution.h"

void isHamiltonianCicle(Graph graph, std::vector<int> path) {
    for(int i = 0; i < path.size(); i++) {
        int source = path.at(i);
        int target = path.at(path.size() % (i + 1));
        if(!graph.isConnected(source, target))
            return false;
    }
    return true;
}

void iteratedSearch(Graph &graph, std::string &startNode) {
    Solution currentSol;
    int numberOfNodes = graph.vertices.size();
    for(int i = graph.getIndexOfVertice(startNode); currentSol.path.size() != numberOfNodes; i++)
        currentSol.path.push_back((i > numberOfNodes) ? numberOfNodes % i : i);

    Solution bestSol = currentSol;
    bool stoppingCriterion = false;
    bool improvement = false;
    do {
        for(int i = 1; i < path.size(); i++) {
            for(int j = i + 1; j < path.size(); j++){
                std::swap(path.at(i), path.at(j));
            }
        }
    } while(stoppingCriterion != false);
}

#endif // ITERATED_SEARCH_H
