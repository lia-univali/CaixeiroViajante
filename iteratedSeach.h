#ifndef ITERATED_SEARCH_H
#define #ITERATED_SEARCH_H

#include "graph.h"
#include "solution.h"

bool isHamiltonianCicle(Graph &graph, std::vector<int> &path) {
    for(int i = 0; i < path.size(); i++) {
        int source = path.at(i);
        int target = path.at(path.size() % (i + 1));
        if(!graph.isConnected(source, target))
            return false;
    }
    return true;
}

Solution iteratedSearch(Graph &graph, std::string &startNode) {
    Solution currentSol;
    int numberOfNodes = graph.vertices.size();
    for(int i = graph.getIndexOfVertice(startNode); currentSol.path.size() != numberOfNodes; i++)
        currentSol.path.push_back((i > numberOfNodes) ? numberOfNodes % i : i);

    Solution bestSol = currentSol;
    bool stoppingCriterion = false;
    bool improvement;
    do {
        improvement = false;
        for(int i = 1; i < path.size() - 1; i++) {
            Sol neighbor;
            neighbor.path = currentSol.path;
            std::swap(neighbor.path.at(i), neighbor.path.at(i + 1));
            neighbor.distance = getPathWeight(sol.path, graph);
            if(neighbor.distance < currentSol.distance) {
                currentSol = neighbor;
                improvement = true;
            }
        }
        if(!improvement) {
            // perturbar solução
        }
    } while(stoppingCriterion != false);
}

#endif // ITERATED_SEARCH_H
