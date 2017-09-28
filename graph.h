#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge {
    int source, target;
    double distance;
    Edge(int source, int target, double distance)
        : source (source), target (target), distance (distance) {}
};

struct Vertice {
    std::string name;
    std::vector<Edge> edges;
    double x, y;
    Vertice(std::string name)
        : name (name) {}
};

class Graph {
public:
    std::vector<Vertice> vertices;
    Graph() {}

    int getIndexOfVertice(std::string name) {
        for(int i = 0; i < vertices.size(); i++)
            if(vertices.at(i).name == name)
                return i;
        throw std::exception();
    }

    std::string getNameOfVertice(int &index) {
        return vertices.at(index).name;
    }

    void addVertice(std::string name) {
        Vertice vertice(name);
        vertices.push_back(vertice);
    }

    bool isConnected(int &source, int &target) {
        std::vector<Edge> &edges = vertices.at(source).edges;
        for(Edge &edge : edges)
            if(edge.target == target)
                return true;
        return false;
    }

    Edge getEdge(int &source, int &target) {
        std::vector<Edge> edges = vertices.at(source).edges;
        for(Edge &edge : edges)
            if(edge.target == target)
                return edge;
        throw std::exception();
    }

    void addEdge(int source, int target, int weight) {
        Edge fromSource(source, target, weight);
        vertices.at(source).edges.push_back(fromSource);
        Edge fromTarget(target, source, weight);
        vertices.at(target).edges.push_back(fromTarget);
    }

    void addEdge(std::string source, std::string target, int weight) {
        int sourceIndex = getIndexOfVertice(source);
        int targetIndex = getIndexOfVertice(target);
        addEdge(sourceIndex, targetIndex, weight);
    }
};

#endif
