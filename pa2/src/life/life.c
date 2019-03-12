#include <stdio.h>
#include <stdlib.h>

int neighborCount(int *arr[], int rows, int cols, int i, int j) {
  int count = 0, r, c;
  int topRow = i - 1, bottomRow = i + 1;
  int leftCol = j - 1, rightCol = j + 1;

  if (topRow < 0) {
    topRow = rows - 1;
  }
  if (bottomRow >= rows) {
    bottomRow = 0;
  }
  if (leftCol < 0) {
    leftCol = cols - 1;
  }
  if (rightCol >= cols) {
    rightCol = 0;
  }

  int rowPath[] = {topRow, i, bottomRow};
  int colPath[] = {leftCol, j, rightCol};

  for (r = 0; r < 3; r++) {
    for (c = 0; c < 3; c++) {
      count += arr[rowPath[r]][colPath[c]];
    }
  }
  count -= arr[i][j];

  return count;
}

int** step(int *arr[], int rows, int cols) {
  int r, c;

  int **b = malloc(rows * sizeof(int *));
  for (r = 0; r < rows; r++) {
    b[r] = malloc(cols * sizeof(int));
  }
  for (r = 0; r < rows; r++) {
    for (c = 0; c < cols; c++) {
      b[r][c] = arr[r][c];
    }
  }

  for (r = 0; r < rows; r++) {
    for (c = 0; c < cols; c++) {
      int nc = neighborCount(arr, rows, cols, r, c);
      if (arr[r][c] == 1 && (nc < 2 || nc > 3)) {
        b[r][c] = 0;
      }
      if (arr[r][c] == 0 && nc == 3) {
        b[r][c] = 1;
      }
    }
  }

  return b;
}

void printBoard(int *arr[], int rows, int cols) {
  int r, c;
  for (r = 0; r < rows; r++) {
    for (c = 0; c < cols; c++) {
      char f = (arr[r][c] ? '*' : '.');
      printf("%c", f);
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char **argv) {
  if (argc - 1 != 2) {
    printf("Invalid number of arguments\n");
    return EXIT_SUCCESS;
  }

  FILE *file = fopen(argv[2], "r");
  int steps = atoi(argv[1]);

  if (steps < 0 || !file) {
    printf("Invalid input\n");
    return EXIT_SUCCESS;
  }

  int rows, cols;
  int r, c;

  int first = fscanf(file, "%d", &rows);
  if (first <= 0) {
    return EXIT_SUCCESS;
  }
  fscanf(file, "%d", &cols);

  int **board = malloc(rows * sizeof(int *));
  for (r = 0; r < rows; r++) {
    board[r] = malloc(cols * sizeof(int));
  }

  char f = '\0';
  for (r = 0; r < rows; r++) {
    for (c = 0; c < cols; c++) {
      fscanf(file, " %c", &f);
      board[r][c] = (f == '*' ? 1 : 0);
    }
  }

  int i;
  for (i = 0; i < steps; i++) {
    board = step(board, rows, cols);
  }

  printBoard(board, rows, cols);

  //free array
  for (r = 0; r < rows; r++) {
    free(board[r]);
  }

  fclose(file);

  return EXIT_SUCCESS;
}
