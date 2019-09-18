#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  size_t i;
  size_t maxSeq = 0;
  size_t store_num[n];
  for (i = 0; i < n; i++) {
    store_num[i] = 0;
  }
  for (i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      maxSeq++;
    }
    else {
      maxSeq = 0;
    }
    store_num[i] = maxSeq + 1;
  }
  size_t max_number = store_num[0];
  for (i = 1; i < n; i++) {
    if (store_num[i] > max_number) {
      max_number = store_num[i];
    }
  }
  return max_number;
}
