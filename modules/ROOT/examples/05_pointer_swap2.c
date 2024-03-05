#include <stdio.h>

void swap(int *, int *);

int main() {
  int a = 1, b = 2;
  int *pa, *pb;
  pa = &a;
  pb = &b;
  printf("before: a = %d, b = %d\n", a, b);
  swap(pa, pb);
  printf("after : a = %d, b = %d\n", a, b);
}

void swap(int *a, int *b) {
  int c;
  c = *a;
  *a = *b;
  *b = c;
  printf("swap  : a = %d, b = %d\n", *a, *b);
}
