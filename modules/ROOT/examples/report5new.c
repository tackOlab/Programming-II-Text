#include <stdio.h>

#include "pgm.h"  // PGM画像の読み書きに必要．Blackboardからダウンロードしておく．

// プロトタイプ宣言
void subsampling(int, int, unsigned char *, unsigned char *);

int main() {
  int width0, height0, maxval;    // 処理前の画像の幅，高さ，ピクセルの最大値
  int width1, height1;            // 処理後の画像の幅，高さ
  unsigned char *input, *output;  // 処理前および処理後の画像のピクセルデータへのポインタ

  // PGM画像の読み込み: 読み込まれたピクセルデータはinputによってアクセス可能になる
  input = read_pgm("./barbara.pgm", &width0, &height0, &maxval);
  // 幅 x 高さ, 最大値の表示 (確認用)
  printf("%d x %d, %d\n", width0, height0, maxval);

  width1 = width0 / 2;
  height1 = height0 / 2;
  // 処理後の画像データのためのメモリを確保
  output = (unsigned char *)malloc(width1 * height1);

  subsampling(width1, height1, input, output);
  // PGM画像の書き込み:
  write_pgm(width1, height1, maxval, "output.pgm", output);

  free(input);   // メモリの解放
  free(output);  // メモリの解放
}

// 関数の定義
void subsampling(int width, int height, unsigned char *input, unsigned char *output) {
  for (int i = 0; i < height; ++i) {
    int pos_in = (i * 2) * width * 2;
    int pos_out = i * width;
    for (int j = 0; j < width; ++j) {
      unsigned char *val = input + pos_in;
      unsigned char *op = output + pos_out;
      *op = *val;
      pos_in += 2;
      pos_out++;
    }
  }
}