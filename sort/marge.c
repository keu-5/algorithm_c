#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 10000

//NOTE: work space array
int b[MAX_ELEMENTS];

void init(int a[], int size) {
  srand(time(NULL));
  for (int i = 0; i < size; i++) {
    a[i] = rand() % 1000;
  }
}

void show(int a[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", a[i]);
  }
}

//NOTE: Merge function to merge two sorted subarrays
void merge(int a[], int low, int mid, int high) {
  int i, j, k;
  i = low;
  j = mid + 1;
  k = low;

  //NOTE: Merge elements from both subarrays into b[]
  while (i <= mid && j <= high) { //PERF: Until each subarrays deviate from the element
    if (a[i] <= a[j]) {
      b[k++] = a[i++];
    } else {
      b[k++] = a[j++];
    }
  }

  //HACK: I don't know why following processes are functioning properly
  //NOTE: Copy remaining elements from the first subarray
  while (i <= mid) {
    b[k++] = a[i++];
  }

  //NOTE: Copy remaining elements from the second subarray
  while (j <= high) {
    b[k++] = a[j++];
  }

  //NOTE: Copy merged elements back to original array a[]
  for (i = low; i <= high; i++) {
    a[i] = b[i];
  }
}

//NOTE: Merge Sort function
void merge_sort(int a[], int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;
    merge_sort(a, low, mid); //PERF: minimum number of elements is 1
    merge_sort(a, mid + 1, high); //PERF: minimum number of elements is 1
    merge(a, low, mid, high);
  }
}

int main(void) {
  int size = 15;
  int a[size];

  init(a, size);
  
  printf("before-array:\n");
  show(a, size);

  merge_sort(a, 0, size - 1);

  printf("\nafter-array:\n");
  show(a, size);

  return 0;
}

