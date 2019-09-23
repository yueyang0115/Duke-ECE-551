#ifndef ELECTION_H
#define ELECTION_H

#include <stdint.h>
#include <stdlib.h>
#define MAX_STATE_NAME_LENGTH 64

struct state_tag {
  char name[MAX_STATE_NAME_LENGTH];
  uint64_t population;
  unsigned int electoralVotes;
};
typedef struct state_tag state_t;

state_t parseLine(const char * line);

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates);

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates);

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates);

#endif
