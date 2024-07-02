#include <stdio.h>
#include <stdlib.h>

#include "pgm.h"

void upsampling(int width, int height, unsigned char *input, unsigned char *output);
int interpolation(int width, int height, unsigned char *data, int algorithm);

int main() {
  int width0, height0, maxval;
  int width1, height1;
  unsigned char *input, *output;

  input = read_pgm("./barbara.pgm", &width0, &height0, &maxval);
  printf("%d x %d, %d\n", width0, height0, maxval);

  width1 = width0 * 2;
  height1 = height0 * 2;
  output = (unsigned char *)malloc(width1 * height1);

  // アップサンプリング
  upsampling(width0, height0, input, output);

  // 補間
  int algorithm = 0;  // 0: ニアレストネイバー法，1: Bilinear法
  if (interpolation(width1, height1, output, algorithm)) {
    return EXIT_FAILURE;
  };
  write_pgm(width1, height1, maxval, "output.pgm", output);
}

void upsampling(int width, int height, unsigned char *input, unsigned char *output) {
  int o_stride = width * 2;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      output[(2 * i) * o_stride + 2 * j] = input[i * width + j];
    }
  }
}

int interpolation(int width, int height, unsigned char *data, int algorithm) {
  int ret = EXIT_SUCCESS;
  switch (algorithm) {
    case 0:  // ニアレストネイバー法による補間
      // 水平方向
      for (int i = 0; i < height; i += 2) {
        for (int j = 0; j < width; j += 2) {
          data[i * width + j + 1] = data[i * width + j];
        }
      }
      // 垂直方向
      /* 自分で考える部分*/
      break;
    case 1:  // バイリニア法による補間
      /* 自分で考える部分*/
      break;

    default:
      printf("ERROR: Unkown algorithm\n");
      ret = EXIT_FAILURE;
      break;
  }
  return ret;
}
