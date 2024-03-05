#include <stdio.h>

double get_average(int *, int);

int main() {
  int data[5] = {1, 3, 2, 4, 8};
  int num_data = 5;
  double average = get_average(&data[0], num_data);
  printf("平均値は%fです\n", average);
}

double get_average(int *in, int N) {
  double sum = 0.0;
  int i;
  for (i = 0; i < N; ++i) {
    sum += (double)in[i];
  }
  return sum / N;
}
