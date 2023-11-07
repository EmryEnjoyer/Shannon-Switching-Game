#include <iostream>
/**
 * This file implements a splay tree according to the Wikipedia interace.
 * We use a functional implementation to reduce the state of Node.
*/

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node<K,V> * left;
    Node<K,V> * right;
    Node<K,V> * parent;
    void print() {
        if(left)
            std::cout << key << " -> " << left->key << " [style=\"solid\" dir=both]" << std::endl;
        if(right)
            std::cout << key << " -> " << right->key << " [style=\"solid\" dir=both]" << std::endl;

        if(left)
            left->print();
        if(right)
            right->print();
    }
    Node(K key, V value) {
        this->key = key;
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
    
};

/**
 * Brings a node to the root, maintaining search-tree structure
 *
 * @param root: The root of the splay tree.
 * @param key: The key of the 
 * @return the new root of the splay tree.
*/
template <typename K, typename V>
Node<K,V> * splay (Node<K,V> * root, K key);

/**
 * Inserts a node into a tree.
 * 
 * @param root: The tree to insert the new node into
 * @param key: The key of the new value to insert
 * @param value: The value to assign to the key.
 * @returns the new root of the tree.
*/
template <typename K, typename V>
Node<K,V> * insert(Node<K,V> * root, K key, V value);

/**
 * Removes a node from a tree.
 * 
 * @param root: root of tree to remove node from
 * @param key: key to remove.
*/
template <typename K, typename V>
Node<K,V> * remove(Node<K,V> * root, K key);

#endif