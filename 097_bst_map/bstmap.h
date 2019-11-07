#include <cstdio>
#include <cstdlib>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL){};
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL){};
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs);
  BstMap & operator=(const BstMap & rhs);
  virtual ~BstMap();
  virtual void add(const K & key, const V & value);
  virtual const V & lookup(const K & key) const throw(std::invalid_argument);
  virtual void remove(const K & key);
  //virtual ~Map<K, V>();
  Node * copy(Node * current);
  Node * addnode(Node * current, const K key, const V value);
  void destroy(Node * current);
  Node * similar(Node * current);
};

//copy constructor
template<typename K, typename V>
BstMap<K, V>::BstMap(const BstMap & rhs) {
  root = copy(rhs.root);
}
//copy helper function
template<typename K, typename V>
typename BstMap<K, V>::Node * BstMap<K, V>::copy(Node * current) {
  if (current == NULL) {
    return NULL;
  }
  Node * mynode = new Node(current->key, current->value);
  mynode->left = copy(current->left);
  mynode->right = copy(current->right);
  return mynode;
}

//assignment operator
template<typename K, typename V>
BstMap<K, V> & BstMap<K, V>::operator=(const BstMap & rhs) {
  if (this != &rhs) {
    BstMap<K, V> tmp(rhs);
    Node * original_root = root;
    root = tmp.root;
    tmp.root = original_root;
  }
  return *this;
}

//destructor
template<typename K, typename V>
BstMap<K, V>::~BstMap() {
  destroy(root);
}
//destroy helper function
template<typename K, typename V>
void BstMap<K, V>::destroy(Node * current) {
  if (current == NULL) {
    return;
  }
  destroy(current->left);
  destroy(current->right);
  delete current;
}

//add
template<typename K, typename V>
void BstMap<K, V>::add(const K & key, const V & value) {
  root = addnode(root, key, value);
}
//add helper function
template<typename K, typename V>
typename BstMap<K, V>::Node * BstMap<K, V>::addnode(Node * current,
                                                    const K key,
                                                    const V value) {
  if (current == NULL) {
    Node * ans = new Node(key, value);
    return ans;
  }
  else {
    if (key == current->key) {
      current->value = value;
    }
    else if (key < current->key) {
      current->left = addnode(current->left, key, value);
    }
    else {
      current->right = addnode(current->right, key, value);
    }
    return current;
  }
}

//lookup
template<typename K, typename V>
const V & BstMap<K, V>::lookup(const K & key) const throw(std::invalid_argument) {
  Node * current = root;
  while (current != NULL) {
    if (key == current->key) {
      return current->value;
    }
    else if (key < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }
  throw std::invalid_argument("key not find\n");
}

//remove
template<typename K, typename V>
void BstMap<K, V>::remove(const K & key) {
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
  if ((*current)->right == NULL) {
    Node * temp = (*current)->left;
    delete (*current);
    *current = temp;
  }
  else {
    Node * similarnode = similar((*current)->left);
    (*current)->key = similarnode->key;
    (*current)->value = similarnode->value;
    remove(similarnode->key);
  }
}

//find similar pass in current->left only need to go right
template<typename K, typename V>
typename BstMap<K, V>::Node * BstMap<K, V>::similar(Node * current) {
  while (current->right != NULL) {
    current = current->right;
  }
  return current;
}
