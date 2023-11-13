#include <vector>
#include <list>
#include <map>
#include <queue>
#include <iostream>
#include <set>
#include "Graph.h"

#pragma once

template <typename V, typename E>
class AdjacencyLists : public Graph<V,E>
{
    std::vector<V> vertices;
    std::map<V, std::list<V>> adjLists;
    std::map<std::pair<V, V>, EdgeCost<E>> edges;
    bool weighted;
    bool isDirected;
    int lastOrder;
public:
    AdjacencyLists(bool isDirected, bool weighted, std::vector<V> vertices);
    AdjacencyLists(bool isDirected, bool weighted);

    /**
     * Insert a vertex into this AdjacencyLists.
    */
    void AddVertex(V vertex);

    bool ContainsVertex(V vert);

    /**
     * Insert an edge into this AdjacencyLists
     * @param src: The source node, we assume that this node is already in the AdjacencyLists
     * @param dst: The destination node, we assume that this node is already in the AdjacencyLists
     * @param cost: The weight of the edge
    */
    void AddEdge(V src, V dst, bool isProtected, E cost=1, int order=-1);

    /**
     * Remove an edge from the AdjacencyLists
     * 
     * @param src: Where does the edge start
     * @param dst: Where does the edge end
    */
    std::pair<std::pair<V, V>, E> RemoveEdge(V src, V dst);

    std::list<V> GetNeighbors(V node);  

    std::vector<V> GetVertices();

    /**
     * Prints the AdjacencyLists out in depth first order from the first entry in Vertices
    */
    // void Print();

    EdgeCost<E> GetEdge(V src, V dst);

    std::map<std::pair<V, V>, EdgeCost<E>> getEdges() {
        return edges;
    }
};

// ====================================================================
// IMPLEMENTATION
// ====================================================================

template <typename V, typename E>
bool AdjacencyLists<V, E>::ContainsVertex(V vert) 
{
    for(auto v : vertices) 
    {
        if(v == vert)
            return true;
    }
    return false;
}

template <typename V, typename E>
AdjacencyLists<V, E>::AdjacencyLists(bool isDirected, bool weighted)
{
    this->vertices = std::vector<V>();
    this->isDirected = isDirected;
    this->weighted = weighted;
    this->adjLists = std::map<V, std::list<V>>();
    this->edges = std::map<std::pair<V, V>, EdgeCost<E>>();
    this->lastOrder = 0;
}

template <typename V, typename E>
AdjacencyLists<V, E>::AdjacencyLists(bool isDirected, bool weighted, std::vector<V> vertices) 
{
    this->vertices = vertices;
    this->isDirected = isDirected;
    this->weighted = weighted;
    this->adjLists = std::map<V, std::list<V>>();
    this->edges = std::map<std::pair<V, V>, EdgeCost<E>>();
    this->lastOrder = 0;
}
template <typename V, typename E>
void AdjacencyLists<V, E>::AddVertex(V vertex) 
{
    for(auto v : vertices)
        if(vertex == v)
            return;
    this->vertices.push_back(vertex);
    this->adjLists[vertex] = std::list<V>();
}

template <typename V, typename E>
void AdjacencyLists<V, E>::AddEdge(V src, V dst, bool isProtected, E cost, int order) 
{
    int nextOrder = (order == -1) ? lastOrder++ : order;
    EdgeCost<E> edgeCost{cost, nextOrder, isProtected};
    this->edges[std::pair<V,V>(src, dst)] = edgeCost;
    if(!(this->isDirected)) {
        this->edges[std::pair<V,V>(dst, src)] = edgeCost;
        (this->adjLists[dst]).push_back(src);
    }
    (this->adjLists[src]).push_back(dst);
}

template <typename V, typename E>
std::pair<std::pair<V, V>, E> AdjacencyLists<V, E>::RemoveEdge(V src, V dst) 
{
    EdgeCost<E> edgeCost = this->edges[std::pair<V,V>(src, dst)];
    std::pair<V, V> edge = std::pair<V,V>(src, dst);
    this->edges[edge] = EdgeCost<E>{0,-1};
    std::list<V> * srcNeighbors = &(this->adjLists[src]);
    std::list<V> * dstNeighbors = &(this->adjLists[dst]);
    srcNeighbors->remove(dst);
    dstNeighbors->remove(src);
    return std::pair<std::pair<V, V>, E>(edge, edgeCost.cost);
}

template<typename V, typename E>
std::list<V> AdjacencyLists<V,E>::GetNeighbors(V node) 
{
    return this->adjLists[node];
}

template<typename V, typename E>
std::vector<V> AdjacencyLists<V, E>::GetVertices() 
{
    return this->vertices;
}

// template<typename V, typename E>
// void AdjacencyLists<V,E>::Print() 
// {
//     V start = this->vertices[0];
// 
//     std::set<V> visited = std::set<V>();
//     std::queue<V> todo = std::queue<V>();
//     todo.push(start);
//     
//     while(!(todo.empty()))
//     {
// 
//         V top = todo.front();
//         todo.pop();
//         if(visited.count(top) != 0)
//             continue;
//         visited.insert(top);
//         std::cout << top << ": ";
//         std::list<V> neighbors = GetNeighbors(top);
//         for(auto neighbor : neighbors) 
//         {
//             if(edges[std::pair<V,V>(top,neighbor)].cost > 0) {
//                 std::cout << top << "-" << neighbor << " " << this->edges[std::pair<V,V>(top, neighbor)].cost << " ";
//                 if(visited.count(neighbor) == 0)
//                     todo.push(neighbor);
//             }
//         }
//         std::cout << "\n";
//     }
// }

template <typename V, typename E>
EdgeCost<E> AdjacencyLists<V,E>::GetEdge(V src, V dst) {
    return this->edges[std::pair<V,V>(src, dst)];
}