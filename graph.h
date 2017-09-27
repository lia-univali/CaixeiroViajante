#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge {
    int origin, target;
    double distance;
    Edge(int origin, int target, double distance) 
        : origin (origin), target (target), distance (distance) {}        
};

using Edges = std::vector<Edge>;

struct Vertice {
    std::string name;
}

class Graph {
public:
    std::vector<Vertice> vertices;
    std::vector<Edges> adjacents;
    Graph() {}
    Graph(std::vector<Vertice> vertices, std::vector<Edge> edges) 
        : vertices (vertices), edges (edges) {}
        
    std::vector<Edge> getAdjacents(int verticeIndex) {
        return adjacents.at(verticeIndex);
    }
    Edge getEdge(int origin, int target) {
        for(Edge edge in adjacents.at(origin))
            if (edge.target == target)
                return edge;
        throw std::exception();
    }
}

#endif