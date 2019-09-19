#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return ((x + 2) * y - 3 * x);
}

void run_check_seq3(int x, int y, int expected_ans) {
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));
  if (seq3(x, y) != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if ((xLow >= xHi) | (yLow >= yHi)) {
    return 0;
  }
  else {
    int Even_num = 0;
    for (int i = xLow; i < xHi; i++) {
      for (int j = yLow; j < yHi; j++) {
        if (seq3(i, j) % 2 == 0) {
          Even_num++;
        }
      }
    }
    return Even_num;
  }
}

void run_check_countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));
}

int main(void) {
  run_check_seq3(-6, -6, 42);
  run_check_seq3(-5, -4, 27);
  run_check_seq3(-4, -3, 18);
  run_check_seq3(-3, -2, 11);
  run_check_seq3(-2, -1, 6);
  run_check_seq3(-1, 0, 3);
  run_check_seq3(1, -1, -6);
  run_check_seq3(2, -2, -14);
  run_check_seq3(3, -3, -24);
  run_check_seq3(4, 3, 6);
  run_check_seq3(5, 4, 13);
  run_check_seq3(-1, 5, 8);

  run_check_countEvenInSeq3Range(0, 2, 0, 3);
  run_check_countEvenInSeq3Range(1, 0, 4, 7);
  run_check_countEvenInSeq3Range(4, 7, 1, 1);
  run_check_countEvenInSeq3Range(-3, 4, 2, 7);
  run_check_countEvenInSeq3Range(-1, 2, -2, 2);
  exit(EXIT_SUCCESS);
}

// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
