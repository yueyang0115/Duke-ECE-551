#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate_matrix(FILE * f) {
  char line[12] = {0};
  char rotate_matrix[10][10] = {{0}};

  for (int j = 0; j < 10; j++) {
    if ((fgets(line, 12, f) != NULL)) {
      if (strchr(line, '\n') == NULL) {
        printf("There is a line with more than ten characters\n");
        exit(EXIT_FAILURE);
      }
      if (line[10] != '\n') {
        printf("There is a line with incorrext number of characters\n");
        exit(EXIT_FAILURE);
      }
      if (line[0] == '\n') {
        printf("There are less than ten lines\n");
        exit(EXIT_FAILURE);
      }
      else {
        for (int i = 0; i < 10; i++) {
          rotate_matrix[i][9 - j] = line[i];
        }
      }
    }
    else {
      printf("There are less than ten lines\n");
      exit(EXIT_FAILURE);
    }
  }

  if (fgets(line, 12, f) != NULL) {
    printf("There are more than ten lines");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (rotate_matrix[i][j] != EOF) {
        printf("%c", rotate_matrix[i][j]);
      }
      else {
        printf("EOF in the middle of the matrix\n");
        exit(EXIT_FAILURE);
      }
    }
    printf("%c", '\n');
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: incorect arg number");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotate_matrix(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
