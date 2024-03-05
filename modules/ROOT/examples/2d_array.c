int data[2][3];  // 2行3列の2次元配列を宣言，添字の有効範囲はdata[0-1][0-2]
int rows = 2;    // 行数（縦の要素数）
int cols = 3;    // 列数 (横の要素数)
int i, j;

// 初期化
for (i = 0; i < rows; ++i) {
  for (j = 0; j < cols; ++j) {
    data[i][j] = 0;
  }
}
// 各行の先頭アドレスを表示
for (i = 0; i < rows; ++i) {
  printf("%x\n", &data[i][0]);
}
// 各行の先頭アドレスを表示(省略形)
for (i = 0; i < rows; ++i) {
  printf("%x\n", data[i]);
}
// (x,y) = (2,1)の要素に値を代入
data[1][2] = 100;
