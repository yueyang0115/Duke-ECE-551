#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> map;
  try {
    map.add(60, 1);
    map.add(19, 2);
    map.add(93, 3);
    map.add(4, 4);
    map.add(25, 5);
    map.add(84, 6);
    map.add(1, 7);
    map.add(11, 8);
    map.add(21, 9);
    map.add(35, 10);
    map.add(70, 11);
    map.add(86, 12);

    std::cout << "Lookup key is: " << 25 << " value is: " << map.lookup(25) << std::endl;
    std::cout << "Lookup key is: " << 60 << " value is: " << map.lookup(60) << std::endl;

    map.remove(8);
    //map.remove(19);
    // map.remove(19);
    //map.remove(70);
    // map.remove(35);

    //map.printing();
    std::cout << "Lookup key is:" << 86 << " value is: " << map.lookup(86) << std::endl;
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
