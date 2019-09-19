#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return 4 * x - 3;
}

void run_check_seq1(int x, int expected_ans) {
  printf("seq1(%d) = %d\n", x, seq1(x));
  if (expected_ans != seq1(x)) {
    // printf("find a broken case in run_check_seq1!\n");
    exit(EXIT_FAILURE);
  }
}

void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
  }
  else {
    for (int i = low; i < high; i++) {
      printf("%d", seq1(i));
      if (i != high - 1) {
        printf(", ");
      }
    }
    printf("\n");
  }
}

void run_check_printSeq1Range(int low, int high) {
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
}

int main(void) {
  run_check_seq1(-5, -23);
  run_check_seq1(0, -3);
  run_check_seq1(11, 41);
  run_check_seq1(-100, -403);
  run_check_seq1(100, 397);
  //printf("test case for Seq1 run successfully\n");
  run_check_printSeq1Range(-2, 6);
  run_check_printSeq1Range(7, 3);
  run_check_printSeq1Range(0, 0);
  run_check_printSeq1Range(-100, -95);
  run_check_printSeq1Range(100, 105);
  //printf("test case for printSeq1range run successfully\n");
  exit(EXIT_SUCCESS);
}

// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
