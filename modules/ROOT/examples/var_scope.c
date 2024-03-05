int main() {
  int a0 = 5;
  {
    int a1 = 10;
    printf("a0 = %d, a1 = %d\n", a0, a1);
  }
  a0 = 0;
  a1 = -1;  // 範囲外のためコンパイルエラーとなる
}
