#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  const char * suffix = ".counts";
  unsigned len = strlen(inputName) + strlen(suffix) + 1;
  char * outputName = malloc(len * sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, suffix);
  return outputName;
}
