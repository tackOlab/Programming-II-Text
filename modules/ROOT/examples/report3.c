#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*	
  ここに関数のプロトタイプ宣言を書く
  関数の定義部分をよく見よう
*/

// グローバル変数の宣言
int score[10][6];
double average[6], stdev[6];
char person_name[10][20], subject_name[5][20];
int num_person; // 学生数
int num_subjects; // 科目数

int main() {
  input(); // ファイルから科目数や得点を読み込み学生数を数える関数
  total(); // 各学生の総得点を計算する関数
  calc_statistics(); // 各科目ごとの平均点と標準偏差を計算する関数
  print();           // 結果を印刷する関数
}

/*==================================================================*/
void input(void) {
  int i, j;
  FILE *fp;

  if ((fp = fopen("report3.dat", "r")) == NULL) {
    /* エラー処理を書く */
  }
  fscanf(fp, "%d", &num_subjects); // 科目数の読み込み
  printf("Number of subjects = %d\n", num_subjects);

  for (i = 0; i < num_subjects; i++) { // 科目名の読み込み
    fscanf(fp, "%s", subject_name[i]);
  }

  num_person = 0;
  while (fscanf(fp, /* ヒント参照 */) != EOF) { // 名前の読込み
    for (i = 0; i < num_subjects; i++) {
      fscanf(fp, /* */); // 整数型の数値として点数を読み込む
    }
    ++num_person; // 学生数をインクリメント
  }
  fclose(fp);
  printf("Number of students = %d\n", num_person);
}

/*==============================================================*/
void total(void) {
  int i, j;
  for (i = 0; i < num_person; i++) {   // 学生ごとのループ（行）
    /* 自分で考える */ = 0;              // 学生ごとに総得点をゼロ初期化
    for (j = 0; j < num_subjects; j++) { // 科目ごとループ（列）
      /* 自分で考える*/ += score[i][j];
    }
  }
}

/*==============================================================*/
void calc_statistics(void) {
  double sum, sqsum, t;
  int i, j;

  for (j = 0; j <= num_subjects; j++) { // 平均点の計算
    /*
			自分で考える
		*/
    average[j] = sum / num_person;
  }
  for (j = 0; j <= num_subjects; j++) { // 標準偏差の計算
    sqsum = 0.0;
    for (i = 0; i < num_person; i++) {
      t = score[i][j] - average[j];
      sqsum += t * t;
    }
    stdev[j] = sqrt(sqsum / num_person);
  }
}

/*==============================================================*/
void print(void) {
  // 結果の印刷
  // 参考：printf関数の書式例
  // 文字列の左づめ書式 "%-10s", 数値の３桁表示書式 "%3d"
}
