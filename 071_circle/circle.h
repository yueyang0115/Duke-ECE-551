#include "point.h"

class Circle {
 private:
  Point c;
  const double r;

 public:
  Circle(Point c_init, double r_init) : c(c_init), r(r_init) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
