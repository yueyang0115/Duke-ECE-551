#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <vector>

#include "function.h"
using namespace std;

class shell {
 private:
  std::string input;
  std::vector<std::string> command;

 public:
  bool exit_flag;
  bool no_fork_flag;
  bool buildin_flag;
  std::map<string, string> variable_map;

 public:
  shell();
  virtual ~shell();
  void initial();
  void getinput();
  /*
  string changevar(string source, const string delim);
  string findvar(string source, int front, int rear);
  int stop_parse(string source);
  string checkslash(string source);
  vector<string> parseinput(string source, const string delim);
  int checkvarname(string source);
  vector<string> parse_set(string source, const string delim);
  vector<string> parse_export(string source, const string delim);
  */
  vector<string> parse(string source, const string delim);

  void checkcmd();
  void printcommand();
  void execute();
  void execute_cd();
  void execute_set();
  void execute_export();
  void execute_rev();
  void checkpath();
  vector<string> fillpath();
  void searchpath();
};
