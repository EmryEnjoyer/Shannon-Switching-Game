
#ifndef LINK_CUT_TREE_H
#define LINK_CUT_TREE_H
#include "SplayTree.h"
#include "Graph.h"
#include <map>
template <typename V>
class LinkCutTree {
    Node<int, V> * root;
    std::map<V, Node<int, V> *> splayMap;
public:
    LinkCutTree(Graph<V,int> representedGraph);
    
    Node<int, V> * access(Node<int, V> node);

    Node<int, V> * getSplayNode(V node);
};

// ====================================================================
// IMPLEMENTATION
// ====================================================================

template<typename V>
LinkCutTree<V>::LinkCutTree(Graph<V,int> representedGraph)
{
    this->splayMap = std::map<V, Node<int, V> *>();

    for(auto v : representedGraph.GetVertices())
    {
        if(!splayMap[v])
        {
            Node<int, V> * newSpayNode = new Node<int,V>();
            splayMap[v] 
        }
    }
}

#endif