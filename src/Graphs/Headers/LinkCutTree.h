
#ifndef LINK_CUT_TREE_H
#define LINK_CUT_TREE_H
#include "SplayTree.h"
#include "Tree.h"
#include <map>
#include <queue>
template <typename V>
class LinkCutTree {
    Node<int, V> * root;
    std::map<V, Node<int, V> *> splayMap;
public:
    LinkCutTree(TreeNode<V,int> * representedTreeNode);
    
    Node<int, V> * access(Node<int, V> * node);

    Node<int, V> * getSplayNode(V node);
};

// ====================================================================
// IMPLEMENTATION
// ====================================================================

template<typename V>
LinkCutTree<V>::LinkCutTree(TreeNode<V,int> * representedTree)
{
    this->splayMap = std::map<V, Node<int, V> *>();

    std::queue<TreeNode<V,int>*> todo = std::queue<TreeNode<V,int>>();
    todo.push(representedTree);
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
            splayMap[child->key]->parent = front;
        }
    }
}

#endif