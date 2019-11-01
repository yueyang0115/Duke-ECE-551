#include <cstdlib>

#include "assert.h"
#include "il.h"

void testList(void) {
  IntList test;
  assert(test.head == NULL && test.tail == NULL && test.size == 0);

  test.addFront(3);
  assert(test[0] == 3 && test.getSize() == 1 && test.head->next == NULL &&
         test.head->prev == NULL && test.tail != NULL && test.tail == test.head);
  test.addBack(5);
  assert(test.size == 2 && test[1] == 5);
  assert(test.head->next->next == NULL && test.head->next->prev == test.head);
  assert(test.tail == test.head->next);

  IntList mylist1;
  assert(mylist1.head == NULL);
  assert(mylist1.tail == NULL);
  assert(mylist1.size == 0);

  mylist1.addFront(4);
  assert(mylist1.size == 1);
  assert(mylist1[0] == 4);
  assert(mylist1.head->data == 4);
  assert(mylist1.tail->data == 4);
  assert(mylist1.tail->next == NULL);
  assert(mylist1.head->prev == NULL);
  assert(mylist1.tail->prev == NULL);
  assert(mylist1.head->next == NULL);

  mylist1.addBack(3);  //4 3
  assert(mylist1.size == 2);
  assert(mylist1.head->data == 4);
  assert(mylist1.head->next->data == 3);
  assert(mylist1.head->next->next == NULL);
  assert(mylist1.tail->data == 3);
  assert(mylist1.tail->prev->data == 4);
  assert(mylist1.tail->prev->prev == NULL);
  assert(mylist1.head->prev == NULL);
  assert(mylist1.tail->next == NULL);
  assert(mylist1[1] == 3);

  mylist1.addFront(1);  //1 4 3
  assert(mylist1.size == 3);
  assert(mylist1.head->data == 1);
  assert(mylist1.head->next->data == 4);
  assert(mylist1.head->next->next->data == 3);
  assert(mylist1.head->next->next->next == NULL);
  assert(mylist1.tail->data == 3);
  assert(mylist1.tail->prev->data == 4);
  assert(mylist1.tail->prev->prev->data == 1);
  assert(mylist1.tail->prev->prev->prev == NULL);
  assert(mylist1.head->prev == NULL);
  assert(mylist1.tail->next == NULL);
  assert(mylist1[0] == 1);

  mylist1.addBack(5);  //1 4 3 5 7
  mylist1.addBack(7);

  mylist1.remove(4);
  assert(mylist1.size == 4);
  assert(mylist1.head->data == 1);
  assert(mylist1.head->next->data == 3);
  assert(mylist1.head->next->next->data == 5);
  assert(mylist1.head->next->next->next->data == 7);
  assert(mylist1.head->next->next->next->next == NULL);
  assert(mylist1.tail->data == 7);
  assert(mylist1.tail->prev->data == 5);
  assert(mylist1.tail->prev->prev->data == 3);
  assert(mylist1.tail->prev->prev->prev->data == 1);
  assert(mylist1.tail->prev->prev->prev->prev == NULL);

  //1 3 5 7
  assert(mylist1.getSize() == 4);
  int node5index = mylist1.find(5);
  assert(node5index == 2);

  mylist1.remove(5);  //1 3 7
  assert(mylist1.head->next->data == 3);
  assert(mylist1.tail->prev->data == 3);
  assert(mylist1.getSize() == 3);
  assert(mylist1[0] == 1);
  assert(mylist1[1] == 3);
  assert(mylist1[2] == 7);

  assert(mylist1.find(1) == 0);

  //assign
  IntList mylist2;
  mylist2 = mylist1;
  assert(mylist2[0] == 1);
  assert(mylist2[1] == 3);
  assert(mylist2[2] == 7);
  assert(mylist2.getSize() == 3);
  assert(mylist2.head->prev == NULL);
  assert(mylist2.head->data == 1);
  assert(mylist2.head->next->data == 3);
  assert(mylist2.head->next->next->data == 7);
  assert(mylist2.tail->next == NULL);
  assert(mylist2.tail->data == 7);
  assert(mylist2.tail->prev->data == 3);
  assert(mylist2.tail->prev->prev->data == 1);
  assert(mylist2.tail->prev->prev->prev == NULL);
  assert(mylist2.head->next->next == mylist2.tail &&
         mylist2.head->next->next->next == NULL);
  assert(mylist2.tail->prev->prev == mylist2.head);
  assert(mylist2.head->next->prev == mylist2.head);

  mylist2.remove(3);
  assert(mylist1.getSize() == 3);
  assert(mylist2.remove(3) == false);

  //copy
  IntList mylist3(mylist1);
  assert(mylist3[0] == 1);
  assert(mylist3[1] == 3);
  assert(mylist3[2] == 7);
  assert(mylist3.getSize() == 3);
  assert(mylist3.head->prev == NULL);
  assert(mylist3.head->data == 1);
  assert(mylist3.head->next->data == 3);
  assert(mylist3.head->next->next->data == 7);
  assert(mylist3.head->next->next->next == NULL);
  assert(mylist3.tail->next == NULL);
  assert(mylist3.tail->data == 7);
  assert(mylist3.tail->prev->data == 3);
  assert(mylist3.tail->prev->prev->data == 1);
  assert(mylist3.tail->prev->prev->prev == NULL);
  assert(mylist3.head->next->next == mylist3.tail &&
         mylist3.head->next->next->next == NULL);
  assert(mylist3.tail->prev->prev == mylist3.head);
  assert(mylist3.head->next->prev == mylist3.head);

  mylist3.remove(3);
  assert(mylist1.getSize() == 3);
  assert(mylist3.head->next == mylist3.tail);
  assert(mylist3.tail->prev == mylist3.head);
  assert(mylist3.tail->prev->next == mylist3.tail);

  mylist1.~IntList();
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
