#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (expected_ans != power(x, y)) {
    printf("find a broken case!");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(1, 2, 1);
  run_check(2, 3, 8);
  run_check(300, 3, 27000000);
  run_check(1256, 3, 1981385216);
  exit(EXIT_SUCCESS);
}
