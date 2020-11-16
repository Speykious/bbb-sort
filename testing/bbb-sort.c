#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "debug.h"

int sort_on_bit(int* arr, int const l, int const nbit, int const msb, int const DEBUG) {
  if (nbit < 0) return 0;

  int* left  = malloc(l * sizeof(int));
  int* right = malloc(l * sizeof(int));
  int il = 0, ir = 0;
  int tibn = msb - nbit;

  // Putting values in left and right arrays
  for (int i = 0; i < l; i++) {
    int v = arr[i];
    if ((v >> nbit) & 1)
      //isn't ANDing it with one unnecessary?
      // Actually, imagine the number 0b00100101, right-shifted with 3
      // 00100101 >> 3 = 00100 <--- There's a 1 we don't want there, the value should be 0
      right[ir++] = v;
    else
      left[il++] = v;
  }

  // Putting back values in the original array
  // Note: `il` will indicate where the values
  // from the right array start to appear here
  for (int i = 0; i < il; i++) arr[i] = left[i];
  for (int i = 0; i < ir; i++) arr[il+i] = right[i];
  free(left); free(right); // free the arrays

  // Recursively sort each part of
  // the array on the previous bit
  int comparisons = l;
  if (DEBUG) {
    indent(tibn);
    printf("\x1b[36m(%d) L:\x1b[0m ", nbit);
    print_array(arr, il);
  }
  if (il > 1)
    comparisons += sort_on_bit(arr, il, nbit-1, msb, DEBUG);
  if (DEBUG) {
    indent(tibn);
    printf("\x1b[31m(%d) R:\x1b[0m ", nbit);
    print_array(arr+il, ir);
  }
  if (ir > 1)
    comparisons += sort_on_bit(arr+il, ir, nbit-1, msb, DEBUG);
  
  if (DEBUG) {
    indent(tibn);
    printf("(%d) All: ", nbit);
    print_array(arr, l);
  }

  return comparisons;
}

int max(int* arr, int const len) {
  if (len < 1) return 0;
  int out = arr[0];
  for (int i = 1; i < len; i++)
    if (arr[i] > out) out = arr[i];
  return out;
}

int bbb_sort(int* arr, int const len, int const DEBUG) {
  int m = max(arr, len);
  int msb = m ? log2(m) : 0;
  printf("MSB (%d) │ ", msb);
  return sort_on_bit(arr, len, msb, msb, DEBUG);
}
