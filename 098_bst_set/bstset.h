#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 public:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL){};
    Node(const K k) : key(k), left(NULL), right(NULL){};
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs);
  BstSet & operator=(const BstSet & rhs);
  virtual ~BstSet();
  virtual void add(const K & key);
  virtual bool contains(const K & key) const;
  virtual void remove(const K & key);
  Node * copy(Node * current);
  Node * addnode(Node * current, const K & key);
  void destroy(Node * current);
};

//copy constructor
template<typename K>
BstSet<K>::BstSet(const BstSet & rhs) {
  root = copy(rhs.root);
}
//copy helper function
template<typename K>
typename BstSet<K>::Node * BstSet<K>::copy(Node * current) {
  if (current == NULL) {
    return NULL;
  }
  Node * mynode = new Node(current->key);
  mynode->left = copy(current->left);
  mynode->right = copy(current->right);
  return mynode;
}

//assignment operator
template<typename K>
BstSet<K> & BstSet<K>::operator=(const BstSet & rhs) {
  if (this != &rhs) {
    BstSet<K> tmp(rhs);
    std::swap(root, tmp.root);
    //Node * original_root = root;
    //root = tmp.root;
    //tmp.root = original_root;
  }
  return *this;
}

//destructor
template<typename K>
BstSet<K>::~BstSet() {
  destroy(root);
}
//destroy helper function
template<typename K>
void BstSet<K>::destroy(Node * current) {
  if (current == NULL) {
    return;
  }
  destroy(current->left);
  destroy(current->right);
  delete current;
}

//add
template<typename K>
void BstSet<K>::add(const K & key) {
  root = addnode(root, key);
}
//add helper function
template<typename K>
typename BstSet<K>::Node * BstSet<K>::addnode(Node * current, const K & key) {
  if (current == NULL) {
    Node * ans = new Node(key);
    return ans;
  }
  else {
    if (key == current->key) {
      return current;
    }
    else if (key < current->key) {
      current->left = addnode(current->left, key);
    }
    else {
      current->right = addnode(current->right, key);
    }
    return current;
  }
}

//contains
template<typename K>
bool BstSet<K>::contains(const K & key) const {
  Node * current = root;
  if (current == NULL) {
    return false;
  }
  while (current != NULL) {
    if (key == current->key) {
      return true;
    }
    else if (key < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }
  return false;
}

//remove
template<typename K>
void BstSet<K>::remove(const K & key) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key == (*current)->key) {
      break;
    }
    else if (key < (*current)->key) {
      current = &(*current)->left;
    }
    else {
      current = &(*current)->right;
    }
  }
  if (*current == NULL) {
    throw std::invalid_argument("key not find\n");
  }
  if ((*current)->left == NULL) {
    Node * temp = (*current)->right;
    delete (*current);
    *current = temp;
  }
  else if ((*current)->right == NULL) {
    Node * temp = (*current)->left;
    delete (*current);
    *current = temp;
  }
  else {
    Node * findnode = (*current)->left;
    while (findnode->right != NULL) {
      findnode = findnode->right;
    }
    K tempkey = findnode->key;
    remove(findnode->key);
    (*current)->key = tempkey;
  }
}
