#include "point.h"

#include <cmath>
#include <cstdio>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}
double Point::distanceFrom(const Point & p) {
  double dx = p.x - x;
  double dy = p.y - y;
  return (std::sqrt)(dx * dx + dy * dy);
}
