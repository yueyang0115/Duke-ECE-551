#include <assert.h>

#include <cmath>
#include <cstdlib>
#include <ostream>

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

int binarySearchForZero(Function<int, int> * f, int low, int high);

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
  assert(ans == expected_ans);
}

int main(void) {
  Function_xy * myfunc = new Function_xy();
  check(myfunc, -1, 4, 0, "normal\n");
  check(myfunc, -4, -1, -2, "all negative\n");
  check(myfunc, 1, 4, 1, "all positive\n");
  check(myfunc, 0, 3, 0, "inclusive zero\n");
  check(myfunc, -4, 0, -1, "exclusive zero\n");
  delete myfunc;
  return EXIT_SUCCESS;
}
