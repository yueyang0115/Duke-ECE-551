#include "function.h"

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
void printprompt() {
  char * curr_dir = get_current_dir_name();
  std::cout << "ffosh:" << curr_dir << "$ ";
  free(curr_dir);
}

void setpath() {
  char * path551 = getenv("PATH");
  if (setenv("ECE551PATH", path551, 1) < 0) {
    perror("set 551PATH failed");
    exit(EXIT_FAILURE);
  }
}

vector<string> parseinput(string source, const string delim, map<string, string> map) {
  vector<string> parsed;
  if (source.size() == 0) {
    return parsed;
  }
  string source_copy = source;
  source_copy = changevar(source_copy, "$", map);
  source_copy = checkslash(source_copy);

  size_t curr = 0;
  size_t prev = 0;
  //  int parse_stop_flag = 1;
  curr = source_copy.find(delim);
  while (curr != std::string::npos) {
    if (curr != prev) {
      parsed.push_back(source_copy.substr(prev, curr - prev));
    }
    /*
    if (parsed[0].c_str() != NULL) {
      parse_stop_flag = stop_parse(parsed[0].c_str());
      if (parse_stop_flag == 0) {
        return parsed;
      }
      }*/
    prev = curr + 1;
    if (source_copy[prev] == '\"') {
      curr = source_copy.find('\"', prev + 1);
      while ((source_copy[curr - 1] == '\\') && (source_copy[curr - 2] != '\\')) {
        source_copy.erase(curr - 1, 1);
        curr = source_copy.find('\"', curr);
      }
      if ((source_copy[curr - 1] == '\\') && (source_copy[curr - 2] == '\\')) {
        source_copy.erase(curr - 1, 1);
        parsed.push_back(source_copy.substr(prev + 1, curr - prev - 2));
        //std::cout << source_copy.substr(prev + 1, curr - prev - 2) << std::endl;
      }
      else {
        parsed.push_back(source_copy.substr(prev + 1, curr - prev - 1));
        //std::cout << source_copy.substr(prev + 1, curr - prev - 1) << std::endl;
      }
      prev = curr + 1;
      curr = source_copy.find(delim, prev);
    }
    else {
      curr = source_copy.find(delim, prev);
    }
  }
  // if (prev != source_copy.length()) {
  if (prev < source_copy.length()) {
    parsed.push_back(source_copy.substr(prev));
    //std::cout << source_copy.substr(prev) << std::endl;
  }
  return parsed;
}

int stop_parse(string source) {
  int stop_parse_flag = 1;
  if (strcmp(source.c_str(), "exit") == 0 || strcmp(source.c_str(), "set") == 0 ||
      strcmp(source.c_str(), "rev") == 0 || strcmp(source.c_str(), "cd") == 0 ||
      strcmp(source.c_str(), "export") == 0) {
    stop_parse_flag = 0;
  }
  return stop_parse_flag;
}

string checkslash(string source) {
  string::iterator it;
  it = source.begin();
  while (it != source.end()) {
    if ((*it == '\\') && (*(it + 1) == '\\') && (*(it + 2) != '\"')) {
      source.erase(it);
    }
    ++it;
  }
  return source;
}
string changevar(string source, const string delim, map<string, string> map) {
  size_t curr = 0;
  size_t prev = 0;
  std::map<string, string>::iterator it;
  prev = source.find(delim);
  while (prev != std::string::npos) {
    curr = source.find(delim, prev + 1);
    if (curr == std::string::npos) {
      source = findvar(source, prev + 1, source.length() - 1, map);
      return source;
    }
    else {
      source = findvar(source, prev + 1, curr - 1, map);
      prev = source.find(delim, prev + 1);
    }
  }
  return source;
}

string findvar(string source, int front, int rear, map<string, string> map) {
  std::map<string, string>::iterator it;
  while (front <= rear) {
    std::string variable = source.substr(front, rear - front + 1);
    it = map.find(variable);
    if (it != map.end()) {
      source.erase(front, rear - front + 1);
      source.insert(front, map[variable]);
      source.erase(front - 1, 1);
      return source;
    }
    rear = rear - 1;
  }
  return source;
}

vector<string> parse_three_argu(string source, const string delim) {
  vector<string> parsed;
  size_t curr = 0;
  size_t prev = 0;
  for (int i = 0; i < 2; i++) {
    curr = source.find(delim, prev);
    if (curr == std::string::npos) {
      parsed.push_back(source.substr(prev));
      return parsed;
      // cout << "Error: command set needs three arguments" << std::endl;
    }
    parsed.push_back(source.substr(prev, curr - prev));
    prev = curr + 1;
  }
  parsed.push_back(source.substr(prev));
  return parsed;
}

vector<string> parse_two_argu(string source, const string delim) {
  vector<string> parsed;
  size_t curr = 0;
  size_t prev = 0;
  curr = source.find(delim, prev);
  if (curr == std::string::npos) {
    parsed.push_back(source.substr(prev));
    return parsed;
  }
  parsed.push_back(source.substr(prev, curr - prev));
  prev = curr + 1;
  parsed.push_back(source.substr(prev));
  return parsed;
}

int checkvarname(string source) {
  int validname = 1;
  for (size_t i = 0; i < source.size(); i++) {
    if (!(isalnum(source[i]) || isalpha(source[i]) || source[i] == '_')) {
      validname = 0;
      return validname;
    }
  }
  return validname;
}
