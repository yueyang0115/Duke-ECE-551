#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

class Error : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The requested item does not exist\n";
  }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(const T & data, Node * p1, Node * p2) : data(data), next(p1), prev(p2){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0){};
  LinkedList(const LinkedList & rhs);
  LinkedList & operator=(const LinkedList & rhs);
  ~LinkedList();

  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item);
  int getSize() const;
};

//copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList & rhs) {
  head = NULL;
  tail = NULL;
  size = rhs.size;
  Node * s = rhs.head;
  while (s != NULL) {
    addBack(s->data);
    s = s->next;
  }
}

//assignment operator
template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs) {
  if (this != &rhs) {
    LinkedList<T> tmp(rhs);
    Node * original_head = head;
    head = tmp.head;
    tmp.head = original_head;
    Node * original_tail = tail;
    tail = tmp.tail;
    tmp.tail = original_tail;
    size = tmp.size;
  }
  return *this;
}

//destructor
template<typename T>
LinkedList<T>::~LinkedList() {
  while (head != NULL) {
    Node * temp = head->next;
    delete head;
    head = temp;
  }
  head = NULL;
  tail = NULL;
  size = 0;
}

//addback
template<typename T>
void LinkedList<T>::addBack(const T & item) {
  tail = new Node(item, NULL, tail);
  if (head == NULL) {
    head = tail;
  }
  else {
    tail->prev->next = tail;
  }
  size++;
}

//addfront
template<typename T>
void LinkedList<T>::addFront(const T & item) {
  head = new Node(item, head, NULL);
  if (tail == NULL) {
    tail = head;
  }
  else {
    head->next->prev = head;
  }
  size++;
}

//remove
template<typename T>
bool LinkedList<T>::remove(const T & item) {
  if (head == NULL) {
    return false;
  }
  else {
    Node * p = head;
    while (p != NULL) {
      if (p->data != item) {
        p = p->next;
      }
      else {
        if (head == tail && tail == p) {
          head = tail = NULL;
        }
        else if (tail == p) {
          tail = p->prev;
          tail->next = NULL;
        }
        else if (head == p) {
          head = p->next;
          head->prev = NULL;
        }
        else {
          p->prev->next = p->next;
          p->next->prev = p->prev;
        }
        delete p;
        size--;
        return true;
      }
    }
    return false;
  }
}

//[]
template<typename T>
T & LinkedList<T>::operator[](int index) {
  Node * p = head;
  int i = index;
  while ((p != NULL) && (i > 0)) {
    p = p->next;
    i--;
  }
  if (p == NULL) {
    throw Error();
  }
  return p->data;
}

//const[]
template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  Node * p = head;
  int i = index;
  while ((p != NULL) && (i > 0)) {
    p = p->next;
    i--;
  }
  if (p == NULL) {
    throw Error();
  }
  return p->data;
}
//find
template<typename T>
int LinkedList<T>::find(const T & item) {
  if (head == NULL) {
    return -1;
  }
  int index = 0;
  Node * p = head;
  while (p != NULL) {
    if (p->data == item) {
      return index;
    }
    p = p->next;
    index++;
  }
  return -1;
}

//getsize
template<typename T>
int LinkedList<T>::getSize() const {
  int mysize = 0;
  for (Node * p = head; p != NULL; p = p->next) {
    mysize++;
  }
  return mysize;
  // return size;
}

#endif
