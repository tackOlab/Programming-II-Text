#include <stdio.h>

int menu(void); // メニュー関数のプロトタイプ宣言
void kuku10(void); // 10進数の九九表を表示する関数のプロトタイプ宣言
void kuku(int); // 10進数以外の九九表表示の関数のプロトタイプ宣言

int main() {
  int num;

  do {
    num = menu();
    if (num == 0) {
      printf("終了します\n");
    } else if (num == 10) {
      kuku10();
    } else if (3 <= num && num <= 16) {
      kuku(num);
    } else {
      printf("表示できるのは3進数から16進数までです．\n");
    }
  } while (num != 0);
}

// メニュー関数
int menu(void) {
  int n;
  printf("何進数の掛け算表を出力しますか? (0で終了): ");
  scanf("%d", &n);
  return n;
}

// 10進数の九九表を表示するユーザ関数
void kuku10(void) { /* 自分で考える */
}

// num進数(10進数以外)の九九表を表示するユーザ関数
void kuku(int num) {
  // ヒント1: num進数一桁同士の掛け算は高々num進数2桁で収まる．
  // ヒント2: 上位の桁は割り算の商，下位の桁は余りで求められる
  // ヒント3: 16進数の表示には文字列を使うのが便利
  //          char c[] = "0123456789ABCDEF";
  //   要素数を省略すると自動的に適切なサイズの配列が確保される
  /* 後は自分で考える */
}
