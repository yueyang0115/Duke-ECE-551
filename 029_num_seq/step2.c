#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  if (abs(x % 4) == 2) {
    return (2 * x);
  }
  else {
    return (x * (x + 3) + 1);
  }
}

void run_check_seq2(int x, int expected_ans) {
  printf("seq2(%d) = %d\n", x, seq2(x));
  if (expected_ans != seq2(x)) {
    exit(EXIT_FAILURE);
  }
}
int sumSeq2(int low, int high) {
  if (low >= high) {
    return 0;
  }
  else {
    int sumSeq2 = 0;
    for (int i = low; i < high; i++) {
      sumSeq2 += seq2(i);
    }
    return sumSeq2;
  }
}

void run_check_sumSeq2(int low, int high) {
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
}

int main(void) {
  run_check_seq2(-4, 5);
  run_check_seq2(-3, 1);
  run_check_seq2(-2, -4);
  run_check_seq2(-1, -1);
  run_check_seq2(0, 1);
  run_check_seq2(1, 5);
  run_check_seq2(2, 4);
  run_check_seq2(3, 19);
  run_check_seq2(4, 29);
  run_check_seq2(5, 41);
  run_check_seq2(6, 12);
  run_check_seq2(14, 28);
  //  printf("test case run successfully for seq2\n");
  run_check_sumSeq2(-4, -1);
  run_check_sumSeq2(0, 2);
  run_check_sumSeq2(3, 6);
  run_check_sumSeq2(9, 7);
  run_check_sumSeq2(2, 2);
  exit(EXIT_SUCCESS);
  //  printf("test case run successfully for sumSeq2\n");
}

// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
