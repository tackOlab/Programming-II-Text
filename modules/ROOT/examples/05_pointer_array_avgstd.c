#include <math.h>  // sqrt()を使うため
#include <stdio.h>

void get_average_stdev(int *, int, double *, double *);

int main() {
  int data[5] = {1, 3, 2, 4, 8};
  int num_data = 5;
  double average, stdev;
  get_average_stdev(&data[0], num_data, &average, &stdev);
  printf("平均値は%f, 分散は%fです\n", average, stdev);
}

void get_average_stdev(int *in, int N, double *average, double *stdev) {
  double sum = 0.0;
  int i;
  for (i = 0; i < N; ++i) {
    sum += (double)in[i];
  }
  *average = sum / N;

  double tmp;
  double var = 0.0;  // 分散
  for (sum = 0.0, i = 0; i < N; ++i) {
    tmp = (double)in[i] - *average;
    tmp *= tmp;
    sum += tmp;
  }
  var = sum / N;
  *stdev = sqrt(var);  // 標準偏差 = 分散の非負の平方根
}
