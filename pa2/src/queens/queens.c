#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int canBeTakenWarrior(int *arr[], int size, int i, int j) {
  int row, col;
  int rowPath[] = {i - 2, i - 1, i + 1, i + 2};
  int colPath[4][2] = {{j - 1, j + 1}, {j - 2, j + 2}, {j - 2, j + 2}, {j - 1, j + 1}};
  for (row = 0; row < 4; row++) {
    for (col = 0; col < 2; col++) {
      int r = rowPath[row];
      int c = colPath[row][col];
      if (r >= 0 && r < size && c >= 0 && c < size) {
        if (arr[r][c] == 3) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int canPlaceWarrior(int *arr[], int size, int i, int j) {
  int row, col;
  int rowPath[] = {i - 2, i - 1, i + 1, i + 2};
  int colPath[4][2] = {{j - 1, j + 1}, {j - 2, j + 2}, {j - 2, j + 2}, {j - 1, j + 1}};
  for (row = 0; row < 4; row++) {
    for (col = 0; col < 2; col++) {
      int r = rowPath[row];
      int c = colPath[row][col];
      if (r >= 0 && r < size && c >= 0 && c < size) {
        if (arr[r][c] == 1 || arr[r][c] == 3) {
          return 0;
        }
      }
    }
  }
  return 1;
}

int canBeTakenColumn(int *arr[], int size, int i, int j) {
  int r;
  for (r = 0; r < size; r++) {
    if (r != i && (arr[r][j] == 1 || arr[r][j] == 3)) {
      return 1;
    }
  }
  return 0;
}

int canBeTakenRow(int *arr[], int size, int i, int j) {
  int c;
  for (c = 0; c < size; c++) {
    if (c != j && (arr[i][c] == 1 || arr[i][c] == 3)) {
      return 1;
    }
  }
  return 0;
}

int canBeTakenNegDiagonal(int *arr[], int size, int i, int j) {
  int r = i, c = j;
  while (r >= 0 && c >= 0) {
    if (r != i && c != j && (arr[r][c] == 1 || arr[r][c] == 3)) {
      return 1;
    }
    r--;
    c--;
  }
  r = i, c = j;
  while (r < 8 && c < 8) {
    if (r != i && c != j && (arr[r][c] == 1 || arr[r][c] == 3)) {
      return 1;
    }
    r++;
    c++;
  }

  return 0;
}

int canBeTakenPosDiagonal(int *arr[], int size, int i, int j) {
  int r = i, c = j;
  while (r < 8 && c >= 0) {
    if (r != i && c != j && (arr[r][c] == 1 || arr[r][c] == 3)) {
      return 1;
    }
    r++;
    c--;
  }
  r = i, c = j;
  while (r >= 0 && c < 8) {
    if (r != i && c != j && (arr[r][c] == 1 || arr[r][c] == 3)) {
      return 1;
    }
    r--;
    c++;
  }

  return 0;
}

int canBeTaken(int *arr[], int size, int i, int j, int warrior) {
  int col = canBeTakenColumn(arr, size, i, j);
  int row = canBeTakenRow(arr, size, i, j);
  int negDiag = canBeTakenNegDiagonal(arr, size, i, j);
  int posDiag = canBeTakenPosDiagonal(arr, size, i, j);
  int warriorTaken = warrior && canBeTakenWarrior(arr, size, i, j);
  return col || row || negDiag || posDiag || warriorTaken;
}

int isValidBoard(int *arr[], int size, int warrior) {
  int r, c;
  for (r = 0; r < size; r++) {
    for (c = 0; c < size; c++) {
      if ((arr[r][c] == 1 || arr[r][c] == 3) && canBeTaken(arr, size, r, c, warrior)) {
        return 0;
      }
    }
  }
  return 1;
}

void printPossiblePositions(int *arr[], int size, int warrior) {
  int r, c;

  for (r = 0; r < size; r++) {
    for (c = 0; c < size; c++) {
      if (arr[r][c] == 1) {
        printf("Q");
        continue;
      }
      if (arr[r][c] == 3) {
        printf("W");
        continue;
      }
      if (!canBeTaken(arr, size, r, c, warrior)) {
        if (warrior && canPlaceWarrior(arr, size, r, c)) {
          printf("w");
          continue;
        }
        printf("q");
        continue;
      }
      printf(".");
    }
    printf("\n");
  }
}

int getPlaceableQueenCount(int *arr[], int size, int warrior, int depth) {
  int count = 0;
  int r, c;

  for (r = 0; r < size; r++) {
    for (c = 0; c < size; c++) {
      if (!arr[r][c] && !canBeTaken(arr, size, r, c, warrior)) {
        int t = 1;
        arr[r][c] = 1;
        if (depth < 1) {
          t += getPlaceableQueenCount(arr, size, warrior, 1);
        }
        arr[r][c] = 0;
        count = fmax(count, t);
      }
    }
  }

  return count;
}

int main(int argc, char **argv) {
  if (argc - 1 < 1 || argc - 1 > 3) {
    printf("Invalid number of arguments\n");
    return EXIT_SUCCESS;
  }

  FILE *file = fopen(argv[argc - 1], "r");

  if (!file) {
    printf("Invalid input\n");
    return EXIT_SUCCESS;
  }

  int size = 8;
  int r, c;

  int **board = malloc(size * sizeof(int *));
  for (r = 0; r < size; r++) {
    board[r] = malloc(size * sizeof(int));
  }

  char f = '\0';
  for (r = 0; r < size; r++) {
    for (c = 0; c < size; c++) {
      int sc = fscanf(file, " %c", &f);
      if (sc <= 0) {
        return 0;
      }
      if (f == '.') {
        board[r][c] = 0;
        continue;
      }
      if (f == 'Q') {
        board[r][c] = 1;
        continue;
      }
      if (f == 'W') {
        board[r][c] = 3;
        continue;
      }
    }
  }

  //0 .
  //1 Q
  //2 q
  //3 W

  int warriorOption = 0;
  if (argc - 2 > 0) {
    if ((argv[1][0] == '-' && argv[1][1] == 'w') || (argv[2][0] == '-' && argv[2][1] == 'w')) {
      warriorOption = 1;
    }
  }

  if (!isValidBoard(board, size, warriorOption)) {
    printf("Invalid\n");
    return 0;
  }
  printPossiblePositions(board, size, warriorOption);

  if (argc - 2 > 0) {
    if ((argv[1][0] == '+' && argv[1][1] == '2') || (argv[2][0] == '+' && argv[2][1] == '2')) {
      int count = getPlaceableQueenCount(board, size, warriorOption, 0);
      if (count == 2) {
        printf("Two or more\n");
      }
      if (count == 1) {
        printf("One\n");
      }
      if (count == 0) {
        printf("Zero\n");
      }
    }
  }

  //free array
  for (r = 0; r < size; r++) {
    free(board[r]);
  }

  fclose(file);

  return EXIT_SUCCESS;
}
