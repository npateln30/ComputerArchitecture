#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void printArray(int *arr[], int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      printf("%d", arr[i][j]);
      if (j != size - 1) {
        printf(" ");
      }
    }
    printf("\n");
  }
}

int getMultiplyElement(int *arr1[], int* arr2[], int size, int r, int c) {
  int sum = 0, i;
  for (i = 0; i < size; i++) {
    sum += arr1[r][i] * arr2[i][c];
  }
  return sum;
}

void raiseExp(int *ans[], int *arr[], int size, int ep) {
  int r, c;

  if (ep == 0) {
    for (r = 0; r < size; r++) {
      for (c = 0; c < size; c++) {
        ans[r][c] = (r == c) ? 1 : 0;
      }
    }
    return;
  }

  if (ep == 1) {
    return;
  }

  int temp[size][size];
  for (r = 0; r < size; r++) {
    for (c = 0; c < size; c++) {
      temp[r][c] = getMultiplyElement(ans, arr, size, r, c);
    }
  }
  for (r = 0; r < size; r++) {
    for (c = 0; c < size; c++) {
      ans[r][c] = temp[r][c];
    }
  }
  ep--;
  if (ep > 1) {
    raiseExp(ans, arr, size, ep);
  }
}

int main(int argc, char **argv) {
  if (argc - 1 != 1) {
    printf("Invalid number of arguments");
    return EXIT_SUCCESS;
  }

  FILE *file = fopen(argv[1], "r");

  int size, i;
  int f = fscanf(file, "%d", &size);
  if (f <= 0) {
    return EXIT_SUCCESS;
  }
  int **arr = malloc(size * sizeof(int *));
  for (i = 0; i < size; i++) {
    arr[i] = malloc(size * sizeof(int));
  }

  // init array
  int r, c;
  for (r = 0; r < size; r++) {
    for (c = 0; c < size; c++) {
      fscanf(file, "%d", &(arr[r][c]));
    }
  }

  int ep;
  fscanf(file, "%d", &ep);

  int *ans[size];
  for (i = 0; i < size; i++) {
    ans[i] = malloc(size * sizeof(int));
  }
  for (r = 0; r < size; r++) {
    for (c = 0; c < size; c++) {
      ans[r][c] = arr[r][c];
    }
  }

  raiseExp(ans, arr, size, ep);
  printArray(ans, size);

  //free array
  for (r = 0; r < size; r++) {
    free(arr[r]);
    free(ans[r]);
  }

  fclose(file);

  return EXIT_SUCCESS;
}
