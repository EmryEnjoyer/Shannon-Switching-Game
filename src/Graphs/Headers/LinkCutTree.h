
#ifndef LINK_CUT_TREE_H
#define LINK_CUT_TREE_H
#include "SplayTree.h"
#include "Tree.h"
#include <map>
#include <queue>
template <typename V>
class LinkCutTree {
    std::map<V, Node<int, V> *> splayMap;
public:
    LinkCutTree(std::vector<TreeNode<V,int> *> representedForestNode);
    
    Node<int, V> * access(Node<int, V> * node);

    Node<int, V> * getSplayNode(V node)
    {
        return splayMap[node];
    }
    Node<int, V> * link(Node<int,V> * v, Node<int,V> * w);
    void cut(Node<int,V> * node);
};

// ====================================================================
// IMPLEMENTATION
// ====================================================================

template<typename V>
LinkCutTree<V>::LinkCutTree(std::vector<TreeNode<V,int> *> representedForest)
{
    this->splayMap = std::map<V, Node<int, V> *>();

    std::queue<TreeNode<V,int>*> todo = std::queue<TreeNode<V,int> *>();
    for(auto treeRoot : representedForest)
    {
        todo.push(treeRoot);
    }
    while(!todo.empty())
    {
        TreeNode<V,int> * front = todo.front();
        todo.pop();
        if(!splayMap[front->key])
            splayMap[front->key] = new Node<int,V>(front->depth, front->key);
        
        for(auto child : front->children)
        {
            todo.push(child);
            splayMap[child->key] = new Node<int,V>(child->depth, child->key);
            splayMap[child->key]->parent = splayMap[front->key];
        }
    }
}

template <typename V>
Node<int, V> * LinkCutTree<V>::access(Node<int, V> * node)
{
    if(!node)
        return node;
    
    splay(node);
    node->right = nullptr;

    Node<int, V> * parent = node->parent;
    if (parent) 
    {
        parent->right = node;
        return access(node);
    }
    return node; // node is the root of a topmost splay tree in the Link Cut Tree.
}

template<typename V>
Node<int, V> * LinkCutTree<V>::link(Node<int,V> * v, Node<int,V> * w)
{

    v = access(v); // assignment technically not necessary
    w = access(w);

    v->right = w;
    w->parent = v;

    return v;
}

template<typename V>
void LinkCutTree<V>::cut(Node<int,V> * node)
{
    assert(node);
    access(node);
    assert(node && !node->right);
    if(node->left)
    {
        node->left->parent = node->parent;
        node->left = nullptr;
    }
    node->parent = nullptr;
}


#endif