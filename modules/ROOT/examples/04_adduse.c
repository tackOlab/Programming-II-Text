int main() {
  int a = 5;
  int b = 10;
  int c = add(a, b);  // 関数addの呼び出し
  printf("%dと%dの和は%dです\n", a, b, c);
  printf("2と3の和は%dです\n", add(2, 3));  // 関数addの呼び出し
}
