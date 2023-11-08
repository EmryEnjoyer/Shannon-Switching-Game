#include <vector>

#ifndef TREE_H
#define TREE_H

template<typename K, typename V>
struct TreeNode
{
    bool isRoot;
    int depth;
    std::vector<TreeNode<K,V>*> children;
    K key;
    V value;
    TreeNode(K key, V value)
    {
        isRoot = true;
        children = std::vector<V>();
        this->key = key;
        this->value = value;
        depth = 0;
    }
    TreeNode(K key, V value, TreeNode<K,V> * parent) 
    {
        parent->children.push_back(this);
        this->key = key;
        this->value = value;
        isRoot = false;
        depth = parent->depth + 1;
    }
};

#endif