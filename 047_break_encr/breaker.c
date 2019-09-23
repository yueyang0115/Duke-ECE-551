#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int find_max(int * array) {
  int index = 0;
  for (int i = 0; i < 25; i++) {
    if (array[i + 1] > array[i]) {
      index = i + 1;
    }
  }
  return index;
}

void find_key(FILE * f) {
  int c;
  int letter[26];
  while ((c = fgetc(f)) != EOF) {
    if ((isalpha(c))) {
      c = tolower(c);
      for (int i = 0; i < 26; i++) {
        if (c == i + 'a') {
          letter[i]++;
        }
      }
    }
  }
  int max_index = find_max(letter);
  int key;
  key = (max_index + 26) % 26 - 4;
  printf("key = %d\n", key);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  find_key(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
