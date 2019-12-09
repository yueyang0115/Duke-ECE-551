#include "shell.h"

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
#include <string>
#include <vector>

//#include "function.h"

using namespace std;
shell::shell() {
  exit_flag = 0;
  no_fork_flag = 0;
  buildin_flag = 0;
}

shell::~shell() {
}

void shell::initial() {
  getinput();
  command = parse(input, " ");
  checkcmd();
}
void shell::getinput() {
  std::getline(std::cin, input);
  if (std::cin.eof() == 1) {
    exit_flag = 1;
  }
}

vector<string> shell::parse(string source, const string delim) {
  string source_copy = source;
  vector<string> parsed;
  parsed = parseinput(source_copy, delim, variable_map);
  return parsed;
}

void shell::checkcmd() {
  if (command.size() == 0) {
    no_fork_flag = 1;
    return;
  }
  if ((command[0][0] != '/') && (command[0][0] != '.')) {
    buildin_flag = 1;
  }
  if (strcmp(command[0].c_str(), "exit") == 0) {
    exit_flag = 1;
    return;
    //printf("find exit\n");
  }
  if (strcmp(command[0].c_str(), "cd") == 0) {
    no_fork_flag = 1;
    command = parse_two_argu(input, " ");
    //printcommand();
    execute_cd();
    return;
  }
  if (strcmp(command[0].c_str(), "set") == 0) {
    no_fork_flag = 1;
    command = parse_three_argu(input, " ");
    // printcommand();
    execute_set();
    return;
  }
  if (strcmp(command[0].c_str(), "export") == 0) {
    no_fork_flag = 1;
    command = parse_two_argu(input, " ");
    //printcommand();
    execute_export();
    return;
  }
  if (strcmp(command[0].c_str(), "rev") == 0) {
    no_fork_flag = 1;
    command = parse_two_argu(input, " ");
    // printcommand();
    execute_rev();
  }
}

void shell::printcommand() {
  typedef std::vector<std::string>::iterator itr;
  for (itr i = command.begin(); i != command.end(); i++) {
    std::cout << *i << std::endl;
  }
}

void shell::checkpath() {
  if ((*command.begin())[0] != '/') {
    // printf("begin searching\n");
    if (command[0][0] == '.' && command[0][1] == '/') {
      char * curr_dirc = get_current_dir_name();
      string dirc = curr_dirc;
      command[0] = dirc + command[0].substr(1);
      if (access(command[0].c_str(), F_OK) == -1) {
        //cout << "Command " << command[0] << " not found" << endl;
      }
    }
    else {
      searchpath();
    }
  }
}

void shell::execute() {
  checkpath();
  const char * filename = command[0].c_str();

  std::vector<const char *> argv;
  for (size_t i = 0; i < command.size(); i++) {
    argv.push_back(command[i].c_str());
  }
  argv.push_back(NULL);

  //printf("begin executing\n");
  // printcommand();
  if ((execve(filename, (char **)&argv[0], environ)) < 0) {
    perror("Error: execve failed");
    return;
  }
}

void shell::execute_cd() {
  if (command.size() == 1) {
    if (chdir(getenv("HOME")) < 0) {
      perror("Error: change to directory HOME failed");
      return;
    }
  }
  if (command.size() == 2) {
    if (chdir(command[1].c_str()) < 0) {
      perror("Error: change to directory failed");
      return;
    }
  }
  if (command.size() > 2) {
    perror("Error: command cd only needs two arguments");
    return;
  }
}

void shell::execute_set() {
  if (command.size() < 3) {
    cout << "Error: command set needs three arguments" << std::endl;
    return;
  }
  int validname = checkvarname(command[1].c_str());
  if (validname == 0) {
    cout << "Error: invalid variable name" << std::endl;
    return;
  }
  else {
    std::map<string, string>::iterator it;
    it = variable_map.find(command[1]);
    if (it == variable_map.end()) {
      variable_map.insert(make_pair(command[1], command[2]));
      if (variable_map.find(command[1]) != variable_map.end()) {
        //  cout << "insert variable in map success" << std::endl;
      }
    }
    else {  // variable exists in map
      variable_map.erase(it);
      variable_map.insert(make_pair(command[1], command[2]));
      if (variable_map.find(command[1]) != variable_map.end()) {
        // cout << "insert variable in map success" << std::endl;
      }
    }
  }
}

void shell::execute_export() {
  if (command.size() < 2) {
    cout << "Error: command export needs two arguments" << std::endl;
    return;
  }
  else {
    std::map<string, string>::iterator it;
    it = variable_map.find(command[1]);
    if (it == variable_map.end()) {
      cout << "Error: variable not found" << std::endl;
      return;
    }
    std::string value;
    value = variable_map[command[1]];
    if ((setenv(command[1].c_str(), value.c_str(), 1) < 0)) {
      perror("Error: put variable in env failed");
      return;
    }
    //cout << "getenv " << command[1] << " = " << getenv(command[1].c_str()) << std::endl;
  }
}

void shell::execute_rev() {
  if (command.size() < 2) {
    cout << "Error: command rev needs two arguments" << std::endl;
    return;
  }
  else {
    std::map<string, string>::iterator it;
    it = variable_map.find(command[1]);
    if (it == variable_map.end()) {
      cout << "Error: variable not found" << std::endl;
      return;
    }
    std::string value;
    value = variable_map[command[1]];
    reverse(value.begin(), value.end());
    variable_map.erase(it);
    variable_map.insert(make_pair(command[1], value));
  }
}

vector<string> shell::fillpath() {
  string ecepath = getenv("ECE551PATH");
  vector<string> parsed_551path = parse(ecepath, ":");
  vector<string> filled_path;
  for (size_t i = 0; i < parsed_551path.size(); i++) {
    string temp = parsed_551path[i] + "/" + command[0];  // 551path/command[0]
    //cout << "temp=" << temp << endl;
    filled_path.push_back(temp);
    //cout << "filled_path=" << filled_path[i] << endl;
  }
  return filled_path;
}
void shell::searchpath() {
  vector<string> filled_path = fillpath();
  for (size_t i = 0; i < filled_path.size(); i++) {
    //cout << "searched_path=" << filled_path[i] << endl;
    if (access(filled_path[i].c_str(), F_OK) != -1) {  //access success
      command[0] = filled_path[i];
      return;
    }
  }
  cout << "Command " << command[0] << " not found" << endl;
}
