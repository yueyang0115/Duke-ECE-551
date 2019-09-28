#include "election.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

void split(char * src, const char * delim, char ** dest, int * count) {
  char * result = NULL;
  result = strtok(src, delim);
  while (result != NULL) {
    *dest = result;
    dest++;
    //*dest++ = result;
    (*count)++;
    result = strtok(NULL, delim);
  }
}

state_t parseLine(const char * line) {
  int count = 0;
  if ((line == NULL) || (strlen(line) == 0)) {
    fprintf(stderr, "Line contains nothing\n");
    exit(EXIT_FAILURE);
  }
  char line_cp[100] = {"\0"};
  char * parse_result[10] = {"\0"};
  strcpy(line_cp, line);
  split(line_cp, ":", parse_result, &count);
  if (count != 3) {
    fprintf(stderr, "Line contains more than three elements\n");
    exit(EXIT_FAILURE);
  }
  state_t state;
  strcpy(state.name, parse_result[0]);
  state.population = atoi(parse_result[1]);
  state.electoralVotes = atoi(parse_result[2]);
  return state;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  return 0;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
}
