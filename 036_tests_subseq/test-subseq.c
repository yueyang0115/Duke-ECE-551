#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_ans) {
  if (expected_ans != maxSeq(array, n)) {
    printf("find a broken case!");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int a0[7] = {1, 1, 2, 4, 5, 7, 9};
  int a1[7] = {0, -4, 2, 4, 9, 7, 6};
  int a2[7] = {1, 2, 4, 4, 9, 7, 5};
  int a3[8] = {1, 9, 10, 11, 2, 1, 4, 5};
  int a4[10] = {-2, -1, 3, 1, 0, -1, -2, 4, 5, 6};
  int a5[] = {0};

  run_check(a0, 7, 6);
  run_check(a1, 7, 4);
  run_check(a2, 7, 3);
  run_check(a3, 8, 4);
  run_check(a4, 10, 4);
  run_check(a5, 0, 0);
  printf("exit success");
  exit(EXIT_SUCCESS);
}
