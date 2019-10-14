#include "point.h"

#include <cmath>
#include <cstdio>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}
double Point::distanceFrom(const Point & p) {
  return (std::sqrt)(p.x * p.x + p.y * p.y);
}
