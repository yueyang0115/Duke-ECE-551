#include <algorithm>  //std::sort
#include <cstdlib>    //EXIT_SUCCESS
#include <fstream>    //std::ifstream
#include <iostream>   //std::cin std::cout std::ceer
#include <vector>     //std::vector

void sort_lines(std::istream & is) {
  std::string str;
  std::vector<std::string> lines;
  while (getline(is, str)) {
    lines.push_back(str);
  }
  if ((is.eof() != 1) && (is.good() != 1)) {
    std::cerr << "error occurs when read lines from file" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::sort(lines.begin(), lines.end());
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}
void sort_file(int argc, char ** argv) {
  for (int i = 1; i < argc; i++) {
    std::ifstream ifs(argv[i], std::ifstream::in);
    if (!ifs.is_open()) {
      std::cerr << "file open fails" << std::endl;
      exit(EXIT_FAILURE);
    }
    sort_lines(ifs);
    ifs.close();
  }
}
int main(int argc, char ** argv) {
  if (argc == 1) {
    sort_lines(std::cin);
  }
  if (argc > 1) {
    sort_file(argc, argv);
  }
  return EXIT_SUCCESS;
}
