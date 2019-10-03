#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->countsdata = NULL;
  counts->numCounts = 0;
  counts->numUnkonwn = 0;
  return counts;
}

void addNewStringToList(counts_t * c, const char * str) {
  c->numCounts++;
  c->countsdata = realloc(c->countsdata, c->numCounts * sizeof(*c->countsdata));
  c->countsdata[c->numCounts - 1] = malloc(sizeof(*c->countsdata[c->numCounts - 1]));
  //c->countsdata[c->numCounts - 1]->string =
  // malloc(sizeof(*c->countsdata[c->numCounts - 1]->string));
  c->countsdata[c->numCounts - 1]->string = strdup(str);
  c->countsdata[c->numCounts - 1]->numString = 1;
}

void addCount(counts_t * c, const char * name) {
  size_t flag = 1;
  if (name != NULL) {
    for (size_t i = 0; i < c->numCounts; i++) {
      if (strcmp(c->countsdata[i]->string, name) == 0) {  //find string
        flag = 0;
        c->countsdata[i]->numString++;
        break;
      }
    }
    if (flag) {
      addNewStringToList(c, name);
    }
  }
  else {
    c->numUnkonwn++;
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->numCounts; i++) {
    fprintf(outFile, "%s : %zd\n", c->countsdata[i]->string, c->countsdata[i]->numString);
  }
  if (c->numUnkonwn != 0) {
    fprintf(outFile, "<unknown> : %zd\n", c->numUnkonwn);
  }
  /*if (fclose(outFile) != 0) {
    fprintf(stderr, "File closed failure\n");
    }*/
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->numCounts; i++) {
    free(c->countsdata[i]->string);
    free(c->countsdata[i]);
  }
  free(c->countsdata);
  free(c);
}
