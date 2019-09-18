#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n <= 1) {
    return 0;
  }
  size_t store_num[n];
  size_t maxSeq = 0;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      maxSeq++;
    }
    else {
      maxSeq = 0;
    }
    store_num[i] = maxSeq + 1;
  }
  size_t max_number = store_num[0];
  for (size_t i = 1; i < n; i++) {
    if (store_num[i] > max_number) {
      max_number = store_num[i];
    }
  }
  return max_number;
}
