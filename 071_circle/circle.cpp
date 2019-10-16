#include "circle.h"

#include <cmath>

void Circle::move(double dx, double dy) {
  c.move(dx, dy);
}

double findmin(double x1, double x2) {
  if (x1 < x2) {
    return x1;
  }
  else {
    return x2;
  }
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = this->c.distanceFrom(otherCircle.c);
  double r1 = this->r;
  double r2 = otherCircle.r;
  if (d > (r1 + r2)) {
    return 0.0;
  }
  if (d <= std::abs(r1 - r2)) {
    double r_min = findmin(r1, r2);
    return M_PI * r_min * r_min;
  }
  double ang1 = acos((r1 * r1 - r2 * r2 + d * d) / (2 * d * r1));
  double ang2 = acos((r2 * r2 - r1 * r1 + d * d) / (2 * d * r2));
  return ang1 * r1 * r1 + ang2 * r2 * r2 - d * r1 * sin(ang1);
}
