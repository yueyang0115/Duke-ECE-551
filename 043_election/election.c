#include "election.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Take in a string from src, split it by delimiter, and store elements in dest, the number of elements is count*/
void split(const char * src, char delimiter, char dest[10][64], size_t * count) {
  const char * p = src;
  const char * pTmp = src;
  const char * x = src;
  const char * q = src;
  size_t i = 0;

  while (*p != '\0') {
    p = strchr(p, delimiter);
    if (p != NULL) {
      strncpy(dest[i], pTmp, p - pTmp);
      i++;
      p++;
      pTmp = p;
    }
    else {
      break;
    }
  }

  x = strchr(src, '\0');
  q = strrchr(src, delimiter);
  if (q != NULL) {
    strncpy(dest[i], q + 1, x - q - 1);  //find element after the last delimiter
  }

  *count = i + 1;  //calculate number of elements
}

/*Take in a string and return a state_t with information filled in*/
state_t parseLine(const char * line) {
  state_t state;
  char delim = ':';
  char parse_result[10][64] = {{0}};
  size_t count = 0;

  if ((line == NULL) || (strlen(line) == 0)) {
    fprintf(stderr, "Line contains nothing\n");
    exit(EXIT_FAILURE);
  }
  else {
    split(line, delim, parse_result, &count);

    if (count != 3) {
      fprintf(stderr, "Line contains more or less than three elements\n");
      exit(EXIT_FAILURE);
    }
    else {
      strcpy(state.name, parse_result[0]);
      state.population = atoi(parse_result[1]);
      state.electoralVotes = atoi(parse_result[2]);
    }
  }
  return state;
}

/*Calculete the total number of received electoral votes*/
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

/*Prints out states that require a recount*/
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

/*Find the max number in an array and return its index*/
size_t max(float * array, size_t nStates) {
  float max_num = array[0];
  size_t index = 0;

  for (size_t i = 1; i < nStates; i++) {
    if (array[i] > max_num) {
      max_num = array[i];
      index = i;
    }
  }
  return index;
}

/*Find the state that Candidate A won the largest percentage of the vote*/
void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  float votePercentage[nStates];
  size_t index = 0;

  for (size_t i = 0; i < nStates; i++) {
    votePercentage[i] = 100 * voteCounts[i] / (float)stateData[i].population;
  }
  index = max(votePercentage, nStates);
  printf("Candidate A won %s with %.2f%% of the vote\n",
         stateData[index].name,
         votePercentage[index]);
}
