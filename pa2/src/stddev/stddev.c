#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getStdDev(double *nums, double avg, int count) {
  double difference = 0;
  int i;
  for (i = 0; i < count; i++) {
    difference += pow(nums[i] - avg, 2);
  }
  return sqrt(difference / count);
}

double getAverage(double *nums, int count) {
  int i;
  double sum = 0;
  for (i = 0; i < count; i++) {
    sum += nums[i];
  }
  return sum / count;
}

int main() {
  double *arr = NULL;

  int sc = 0, count = 0;
  double n = 0;

  sc = scanf("%lf", &n);
  while (sc > 0) {
    if (arr == NULL) {
      arr = malloc(sizeof(double));
    }
    else {
      arr = realloc(arr, (count + 1) * sizeof(double));
    }
    arr[count] = n;
    count++;
    sc = scanf("%lf", &n);
  }

  if (arr) {
    double avg = getAverage(arr, count);
    double stddev = 0;
    if (avg != 0) {
      stddev = getStdDev(arr, avg, count);
    }
    printf("mean: %.0f\n", avg);
    printf("stddev: %.0f\n", stddev);
  }
  else {
    printf("no data\n");
  }

  if (arr) {
    free(arr);
  }

  return EXIT_SUCCESS;
}
