#include "election.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

//Fuction split will split a string in dest by delim, and store the result in src
void split(char * src, const char * delim, char ** dest, size_t * count) {
  char * result = NULL;
  result = strtok(src, delim);
  while (result != NULL) {
    *dest = result;
    dest++;
    (*count)++;
    result = strtok(NULL, delim);
  }
}

state_t parseLine(const char * line) {
  size_t count = 0;
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
  size_t count = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] * 2 > (stateData[i].population)) {
      count = count + stateData[i].electoralVotes;
    }
  }
  return count;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  float votePercentage[nStates];
  for (size_t i = 0; i < nStates; i++) {
    votePercentage[i] = 100 * voteCounts[i] / (float)stateData[i].population;
    if ((votePercentage[i] >= 49.5) && (votePercentage[i] <= 50.5)) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             votePercentage[i]);
    }
  }
}

size_t max(float * array, size_t nStates) {
  float max_num = array[0];
  size_t index = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (array[i] > max_num) {
      max_num = array[i];
      index = i;
    }
  }
  return index;
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  float votePercentage[nStates];
  for (size_t i = 0; i < nStates; i++) {
    votePercentage[i] = 100 * voteCounts[i] / (float)stateData[i].population;
  }
  size_t index = max(votePercentage, nStates);
  printf("Candidate A won %s with %.2f%% of the vote\n",
         stateData[index].name,
         votePercentage[index]);
}
