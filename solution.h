#ifndef SOLUTION_H
#define SOLUTION_H

struct Solution {
    std::vector<int> path;
    float weight;
    Solution() {
        weight = INT_MAX;
    }
};

float getPathWeight(std::vector<int> &path, Graph &graph) {
    float weight = 0;
    int source, target;
    for(int i = 0; i < path.size(); i++){
        source = path.at(i);
        target = (i + 1 < path.size()) ? path.at(i + 1) : path.at(0);
        if(graph.isConnected(source, target))
            weight += graph.getEdge(source, target).distance;
        else
            return -1; // caso não haja navegação de um trajeto entre duas cidades, ou seja, inadmissível
    }
    return weight;
}

void printPath(int &startNode, const std::vector<int> &path) {
    std::cout << startNode;
    for(int vertice : path)
        std::cout <<  " => " << vertice;
    std::cout << std::endl;
}

#endif // SOLUTION_H
