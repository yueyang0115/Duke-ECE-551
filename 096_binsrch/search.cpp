#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  high = high - 1;
  int mid;
  while (low < high) {
    mid = (low + high) / 2;
    int guess = f->invoke(mid);
    if (guess == 0) {
      return 0;
    }
    if (guess > 0) {
      high = mid - 1;
    }
    else {
      low = mid + 1;
    }
  }
  if (mid < 0) {
    return high;
  }
  if (mid > 0) {
    return low;
  }
  else {
    return mid;
  }
}
