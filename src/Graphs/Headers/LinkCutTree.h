
#ifndef LINK_CUT_TREE_H
#define LINK_CUT_TREE_H
#include "SplayTree.h"
#include "Graph.h"
template <typename V>
class LinkCutTree {
    Node<int, V> * root;
public:
    LinkCutTree(Graph<V,int> representedGraph);
};

#endif