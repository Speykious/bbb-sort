/**
 * The BBB sorting algorithm (Bit By Bit)
 * Made by Speykious and VOID
 * Probably already exists but
 * we did it anyway ¯\_(ツ)_/¯
 */

#include <stdlib.h>
#include <math.h>


/** The core recursive function */
void sort_on_bit(int* arr, int const length, int const bit_idx) {
  // Don't do anything if nbit < 0
  if (bit_idx < 0) return;
	
  int* left  = malloc(length * sizeof(int));
  int* right = malloc(length * sizeof(int));
  // Keeping track of the number of elements in each array
  int idxl = 0, idxr = 0;

  // Putting values in left and right arrays
  for (int i = 0; i < length; i++) {
    int v = arr[i]; // The current value
    if ((v >> bit_idx) & 1)
      right[idxr++] = v;
    else
      left[idxl++] = v;
  }

  // Putting back values in the original array
  // Note: `idxl` will indicate where in arr the
  // values from the right array start to appear
  for (int i = 0; i < idxl; i++) arr[i] = left[i];
  for (int i = 0; i < idxr; i++) arr[idxl+i] = right[i];
  free(left); free(right); // free the arrays

  // Recursively sort each part of the array on the previous bit
  // We don't need to sort anything if the length is less than 2
  if (idxl > 1) sort_on_bit(arr, idxl, bit_idx-1);
  if (idxr > 1) sort_on_bit(arr+idxl, idxr, bit_idx-1);
}


// Simple (and unsafe) max function
int max(int* arr, int const length) {
  int out = arr[0];
  for (int i = 1; i < length; i++)
    if (arr[i] > out) out = arr[i];
  return out;
}


// Wrapper function, actual bbb_sort
void bbb_sort(int* arr, int const length) {
  int m = max(arr, length); // The maximum number
  int msb = m ? log2(m) : 0; // The Most Significant Bit of m
  sort_on_bit(arr, length, msb);
}
