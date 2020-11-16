#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bbb-sort.h"

#define DEBUG 0 // Whether we want to print things for debugging

int* create_random_array(int const length, int const min, int const max) {
  int* out = malloc(length * sizeof(int));
  for (int i = 0; i < length; i++)
    out[i] = min + rand() % (max - min);
  return out;
}

int main() {
  srand(time(NULL));
  clock_t start, end;
  double cpu_time_used;

  for (int len = 1; len < 10000000; len*=10) {
    for (int i = 0; i < 5; i++) {
      int* arr = create_random_array(len, 0, 1000 /* 0xefffffff */);
      //printf("\x1b[1mArray before sorting:\x1b[0m ");
      //print_array(arr, len);
      //printf("\n");
    
      start = clock();
      int comparisons = bbb_sort(arr, len, DEBUG);
      end = clock();
    
      //printf("\n\x1b[1mArray after sorting:\x1b[0m ");
      //print_array(arr, len);
    
      cpu_time_used = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
      printf("\x1b[33m%f ms\x1b[0m │ ", cpu_time_used);
      printf("\x1b[33m%d\x1b[0m for \x1b[33m%d\x1b[0m els", comparisons, len);
      printf(" │ F = %f %%\n", cpu_time_used * 100.0 / (double)len);
      free(arr);
    }
  }
  
  return 0;
}
