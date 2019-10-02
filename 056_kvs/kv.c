#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//split src, store in kvpair
kvpair_t * fillpair(const char * line, char delimiter) {
  const char * p = line;
  const char * x = line;
  p = strchr(p, delimiter);
  x = strchr(line, '\n');  //the last two characters are '\n''\0'

  if ((p == NULL) || (x == NULL)) {
    fprintf(stderr, "Line contains no delimiter\n");
    exit(EXIT_FAILURE);
  }

  kvpair_t * newpair = malloc(sizeof(*newpair));

  size_t key_len = p - line + 1;  //add more '\0'
  newpair->key = malloc(key_len * sizeof(*newpair->key));
  strncpy(newpair->key, line, key_len - 1);
  newpair->key[key_len - 1] = '\0';

  size_t value_len = x - p;
  newpair->value = malloc(value_len * sizeof(*newpair->value));
  strncpy(newpair->value, p + 1, value_len - 1);
  newpair->value[value_len - 1] = '\0';

  return newpair;
}

void addpair(const char * line, kvarray_t * kvarray) {
  kvpair_t * newpair = NULL;
  newpair = fillpair(line, '=');

  kvarray->pairdata =
      realloc(kvarray->pairdata, (kvarray->numPairs + 1) * sizeof(*kvarray->pairdata));
  kvarray->pairdata[kvarray->numPairs] = newpair;
  kvarray->numPairs++;

  newpair = NULL;

  //free(newpair->key);
  //free(newpair->value);
  //free(newpair);
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    return NULL;
  }

  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;

  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->pairdata = NULL;
  kvarray->numPairs = 0;
  while ((len = getline(&line, &sz, f)) >= 0) {
    addpair(line, kvarray);
  }
  free(line);

  if (fclose(f) != 0) {
    fprintf(stderr, "Close File Error.\n");
    return NULL;
  }
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->numPairs; i++) {
    free(pairs->pairdata[i]->key);
    free(pairs->pairdata[i]->value);
    free(pairs->pairdata[i]);
  }
  free(pairs->pairdata);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->numPairs; i++) {
    printf(
        "key = '%s' value = '%s'\n", pairs->pairdata[i]->key, pairs->pairdata[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->numPairs; i++) {
    if (strcmp(pairs->pairdata[i]->key, key) == 0) {
      return pairs->pairdata[i]->value;
    }
  }
  return NULL;
}
