#include <stdio.h>

int add2(int, int);  // 関数のプロトタイプ宣言

int main() {
  int a = 5;
  int b = 10;
  int c = add2(a, b);  // 関数addの呼び出し
  printf("%d+2と%d+2の和は%dです\n", a, b, c);
}

// 関数の定義(実体)
int add2(int x, int y) {
  int z;
  x += 2;  // xに2を加算
  y += 2;  // yに2を加算
  z = x + y;
  return z;  // zの値を戻り値として返す
}
