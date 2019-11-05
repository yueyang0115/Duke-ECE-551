#include <assert.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class Function_xy : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

extern int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int max_invoke;
  if (high > low) {
    max_invoke = log2(high - low) + 1;
  }
  else {
    max_invoke = 1;
  }
  CountedIntFn * wrap_func = new CountedIntFn(max_invoke, f, mesg);
  int ans = binarySearchForZero(wrap_func, low, high);
  delete wrap_func;
  if (ans != expected_ans) {
    fprintf(stderr, "answer is wrong\n");
    exit(EXIT_FAILURE);
  }
  if (ans == expected_ans) {
    printf("testcase success\n");
  }
}

int main(void) {
  Function_xy * myfunc = new Function_xy();
  printf("checking normal\n");
  check(myfunc, -1, 4, 0, "normal\n");
  printf("checking negative\n");
  check(myfunc, -4, -1, -2, "all negative\n");
  printf("checking positive\n");
  check(myfunc, 1, 4, 1, "all positive\n");
  printf("checking inclusive zero\n");
  check(myfunc, 0, 3, 0, "inclusive zero\n");
  printf("checking exclusive zero\n");
  check(myfunc, -4, 0, -1, "exclusive zero\n");
  printf("checking low equals to high\n");
  check(myfunc, -2, -2, -2, "low equals high\n");
  delete myfunc;
  return EXIT_SUCCESS;
}
