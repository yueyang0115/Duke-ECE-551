#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> map;

  map.add(50, 1);
  map.add(70, 2);
  map.add(35, 3);

  std::cout << "Lookup key is: " << 50 << " value is: " << map.lookup(50) << std::endl;
  std::cout << "Lookup key is: " << 70 << " value is: " << map.lookup(70) << std::endl;

  // map.remove(50);
  //map.remove(70);
  map.remove(35);

  std::cout << "Lookup key is:" << 35 << " value is: " << map.lookup(35) << std::endl;

  return EXIT_SUCCESS;
}
