#include <ctype.h>  //文字検査関数のために必須
#include <stdio.h>

int main() {
  int c;
  FILE *fp;
  fp = fopen("myText.txt", "r");

  c = getc(fp);

  if (isdigit(c)) {
    printf("読み込んだ文字%cは数字です．\n", c);
  } else {
    printf("読み込んだ文字%cは数字では有りません．\n", c);
  }

  fclose(fp);
}
