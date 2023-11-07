#include "Headers/SplayTree.h"
#include <cassert>

template <typename K, typename V>
Node<K,V> * splay (Node<K,V> * root, K key) 
{
    Node<K,V> * keyNode = root;

    while(keyNode && keyNode->key != key)
    {
        if(key < keyNode->key)
            keyNode = keyNode->left;
        else
            keyNode = keyNode->right;
    }
    if(!keyNode)
        return root; // Did not find a value, set root as the new root.
    while(keyNode->parent) {
        keyNode = rotateUp(keyNode);
    }
    return keyNode;
}

template<typename K, typename V>
Node<K,V> * rotateLeft(Node<K,V> * root)
{
    Node<K,V> * pivot = root->right;
    if(!pivot)
        return root; // We could not pivot this node
    
    Node<K,V> * newRight = pivot->left; // New right node for the root.
    Node<K,V> * rootParent = root->parent;

    pivot->parent = root->parent;
    if(root->parent)
        if(root->parent->left == root)
            root->parent->left = pivot;
        else
            root->parent->right = pivot;
    
    root->right = newRight;
    if(root->right) // If newRight points to a valid node...
        root->right->parent = root;
    pivot->left = root;
    root->parent = pivot;
    return pivot; // Pivot is now the root of this subtree
}

template<typename K, typename V>
Node<K,V> * rotateRight(Node<K,V> * root)
{
    Node<K,V> * pivot = root->left;
    if(!pivot)
        return root; // We could not pivot this node
    
    Node<K,V> * newLeft = pivot->right; // New left node for the root.
    Node<K,V> * rootParent = root->parent;

    pivot->parent = root->parent;
    if(root->parent)
        if(root->parent->left == root)
            root->parent->left = pivot;
        else
            root->parent->right = pivot;
    
    root->left = newLeft;
    if(root->left) // If newLeft points to a valid node...
        root->left->parent = root;
    pivot->right = root;
    root->parent = pivot;
    return pivot; // Pivot is now the root of this subtree
}

template<typename K, typename V>
Node<K,V> * rotateUp(Node<K,V> * node) 
{
    // We assume that the node has a valid parent
    assert(node->parent);

    Node<K,V> * root = node->parent;
    if(root->right == node)
        root = rotateLeft(root);
    else 
        root = rotateRight(root);
    return root;
}

template <typename K, typename V>
Node<K,V> * insert(Node<K,V> * root, K key, V value)
{
    Node<K,V> * current = splay(root, key);
    if(current->key == key)
        return current;
    
    Node<K,V> * prev;
    while(current != nullptr) 
    {
        prev = current;
        if(key > current->key)
            current = current->right;
        else
            current = current->left;
    }

    Node<K,V> * newNode = new Node<K,V>(key, value);

    if(key > prev->key) 
        prev->right = newNode;
    else 
        prev->left = newNode;
    newNode->parent = prev;
    while(newNode->parent)
        newNode = rotateUp(newNode);
    return newNode;
}

template <typename K, typename V>
Node<K,V> * remove(Node<K,V> * root, K key)
{
    root = splay(root, key);

    Node<K,V> * nextVal = root->right;
    if(!nextVal) {
        Node<K,V> * newRoot = root->left;
        delete root;
        if(newRoot)
            newRoot->parent = nullptr;
        return newRoot;
    }
    while(nextVal->left)
        nextVal = nextVal->left;
    
    root->key = nextVal->key;
    root->value = nextVal->value;
    
    if(nextVal->parent->left == nextVal)
        nextVal->parent->left = nextVal->right;
    else
        nextVal->parent->right = nextVal->right;
    delete nextVal;
    return root;
}

int main() {
    Node<int,int> *root = new Node(1,1);
    root = insert(root, 5, 3);
    root->print();
    std::cout << " ------ \n";
    root = insert(root, 10, 11);
    root->print();
    std::cout << " ------ \n";
    root = insert(root, 7, 11);
    root->print();
    std::cout << " ------ \n";
    root = insert(root, 123, 456);
    root->print();
    std::cout << " ------ \n";
    root = splay(root, 5);
    root->print();
    std::cout << " ------ \n";
    
    root = remove(root, 1);
    root->print();
    std::cout << " ------ \n";
}