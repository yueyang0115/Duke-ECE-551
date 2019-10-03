#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * counts = createCounts();
  char * line = NULL;
  size_t sz;
  ssize_t len = 0;

  FILE * f = fopen(filename, "r");
  while ((len = getline(&line, &sz, f)) >= 0) {
    char * p = strchr(line, '\n');
    size_t len = p - line;
    char * value = malloc((len + 1) * sizeof(*value));
    strncpy(value, line, p - line);
    value[len] = '\0';
    addCount(counts, lookupValue(kvPairs, value));
    free(value);
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "File closed failure");
  }
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  //count from 2 to argc (call the number you count i)
  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)
  //compute the output file name from argv[i] (call this outName)
  //open the file named by outName (call that f)
  //print the counts from c into the FILE f
  //close f
  //free the memory for outName and c
  //free the memory for kv
  if (argc < 3) {
    fprintf(stderr, "Wrong input files\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);
    FILE * f = fopen(outName, "w");
    if (f != NULL) {
      printCounts(c, f);
    }
    free(outName);
    freeCounts(c);
    if (fclose(f) != 0) {
      fprintf(stderr, "File closed failure\n");
    }
  }
  freeKVs(kv);

  return EXIT_SUCCESS;
}
