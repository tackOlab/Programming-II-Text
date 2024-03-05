#include <stdio.h>

int add(int, int);  // 関数のプロトタイプ宣言

int main() {
  int a = 5;
  int b = 10;
  int c = add(a, b);  // 関数addの呼び出し
  printf("%dと%dの和は%dです\n", a, b, c);
  printf("2と3の和は%dです\n", add(2, 3));  // 関数addの呼び出し
}

// 関数の定義(実体)
int add(int x, int y) {
  int z;
  z = x + y;
  return z;  // zの値を戻り値として返す
}
