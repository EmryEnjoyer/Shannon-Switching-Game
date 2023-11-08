
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

    Node<int, V> * getSplayNode(V node)
        return splayMap[node];
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

template <typename V>
Node<int, V> * LinkCutTree<V>::access(Node<int, V> * node)
{
    if(!node)
        return node;
    
    splay(node);
    node->right = nullptr;

    Node<int, v> parent = node->parent;
    if (parent) {
        parent->right = node;
        return access(node);
    }
    return node; // node is the root of a topmost splay tree in the Link Cut Tree.
}

#endif