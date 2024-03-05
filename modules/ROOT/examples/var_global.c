int g_a1 = 0;  // グローバル変数
int main() {
  int a0 = 5;
  printf("a0 = %d, g_a1 = %d\n", a0, g_a1);
  a0 = 0;
  g_a1 = -1;
  printf("a0 = %d, g_a1 = %d\n", a0, g_a1);
}
