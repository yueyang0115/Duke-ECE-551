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

void printprompt();
void setpath();

vector<string> parseinput(string source, const string delim, map<string, string> map);
int stop_parse(string source);
string checkslash(string source);
string changevar(string source, const string delim, map<string, string> map);
string findvar(string source, int front, int rear, map<string, string> map);
vector<string> parse_three_argu(string source, const string delim);
vector<string> parse_two_argu(string source, const string delim);
int checkvarname(string source);
