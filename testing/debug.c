#include <stdio.h>

void print_array(int* arr, int const length) {
  printf("[");
  for (int i = 0; i < length; i++) {
    if (i) printf(", ");
    printf("\x1b[32m%d\x1b[0m", arr[i]);
  }
  printf("]\n");
}

// Indents text line in stdout by some amount of levels
void indent(int const level) {
  for (int i = 0; i < level; i++)
    printf("\x1b[2m│\x1b[0m ");
}

