#include <utility>
#include <list>
#include <vector>


#pragma once


template <typename E>
struct EdgeCost {
    E cost;
    int order;
    bool isProtected;
};

template <typename V, typename E>
struct Edge {
    std::pair<V,V> edge;
    E cost;
    int order;

    bool operator< (const Edge<V,E> &rhs) const {
        return this->cost < rhs.cost;
    }

    bool operator> (const Edge<V,E> &rhs) const {
        return this->cost > rhs.cost;
    }

    bool operator== (const Edge<V,E> &rhs) const {
        return this->order == rhs.order;
    }
};

/**
 * This interface acts as an abstract implementation of a Graph<V,E>
 * Because we would like our code to be agnostic of the type of graph passed in
 * V is the vertex space, E is the space that the Edge 
*/

template<typename V, typename E>
class Graph {
public:
    virtual void AddVertex(V vert) = 0;

    virtual void AddEdge(V src, V dst, bool isProtected, E cost=1, int order=-1) = 0;

    virtual std::pair<std::pair<V, V>, E> RemoveEdge(V src, V dst) = 0;

    virtual std::list<V> GetNeighbors(V node) = 0;

    virtual std::vector<V> GetVertices() = 0;

    virtual bool ContainsVertex(V vert) = 0;

    virtual void Print() = 0;

    virtual EdgeCost<E> GetEdge(V src, V dst) = 0;

};