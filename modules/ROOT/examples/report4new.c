/*
 * report4new.c -- 固定小数点演算とLUTによる立方根・平方根の近似
 *
 * 本骨格は以下の5つの課題から成る:
 *   課題4-1: Q16形式と double の相互変換 f2q(), q2f() を実装する．
 *   課題4-2: Q16形式の加算 q_add() と乗算 q_mul() を実装する．
 *   課題4-3: LUTを用いた立方根の近似 (最近傍) cbrt_q16_nearest() を実装する．
 *   課題4-4: LUTを用いた立方根の近似 (線形補間) cbrt_q16_linear() を実装する．
 *   課題4-5: LUTを用いた平方根の近似 (線形補間) sqrt_q16_linear() を実装する．
 *           (LUT 構築関数 init_sqrt_lut() も自分で実装)
 *
 * Q16形式: 16bit符号なし整数で [0, 1) の実数を表現する固定小数点形式．
 *   0x0000 →  0.0
 *   0x8000 →  0.5
 *   0xFFFF →  約 0.99998 (1.0は表現不可)
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Q16形式の型定義 */
typedef uint16_t q16_t;

/* プロトタイプ宣言 */
int    menu(void);
q16_t  f2q(double x);
double q2f(q16_t q);
q16_t  q_add(q16_t a, q16_t b);
q16_t  q_mul(q16_t a, q16_t b);
void   init_cbrt_lut(void);
q16_t  cbrt_q16_nearest(q16_t x);
q16_t  cbrt_q16_linear(q16_t x);
void   init_sqrt_lut(void);
q16_t  sqrt_q16_linear(q16_t x);
void   evaluate(q16_t (*approx)(q16_t), double (*truefn)(double), const char *name);
void   task1_warmup(void);
void   task2_basics(void);
void   task3_lut_nearest(void);
void   task4_lut_linear(void);
void   task5_sqrt_lut(void);

/*==============================================================*/
/*  課題4-1: Q16形式と double の相互変換                          */
/*==============================================================*/

/*
 * f2q: double 型の x ∈ [0, 1) を Q16形式 (q16_t) に変換する．
 *      範囲外の値は飽和させる．
 */
q16_t f2q(double x) {
  /* 自分で考える */
  return 0;
}

/*
 * q2f: Q16形式 (q16_t) の q を double 型の実数 ∈ [0, 1) に変換する．
 */
double q2f(q16_t q) {
  /* 自分で考える */
  return 0.0;
}

void task1_warmup(void) {
  /* 何点かの double を Q16 に変換し，q2f で戻して一致を確認する */
  double samples[] = {0.0, 0.25, 0.5, 0.75, 0.99998, -0.1, 1.5};
  int n = sizeof(samples) / sizeof(samples[0]);
  printf("--- 課題4-1: f2q / q2f の動作確認 ---\n");
  printf("   double 入力       Q16表現    q2f で戻した値\n");
  for (int i = 0; i < n; ++i) {
    q16_t q = f2q(samples[i]);
    printf("  %12.6f     0x%04X      %.6f\n", samples[i], q, q2f(q));
  }
}

/*==============================================================*/
/*  課題4-2: Q16形式の加算と乗算                                  */
/*==============================================================*/

/*
 * q_add: Q16同士の飽和加算．結果が 0xFFFF を超える場合は 0xFFFF に飽和させる．
 *        中間結果の型に注意．
 */
q16_t q_add(q16_t a, q16_t b) {
  /* 自分で考える */
  return 0;
}

/*
 * q_mul: Q16同士の乗算．「16bit×16bit→32bit中間→上位16bitを取り出す」構成．
 *        中間結果の型とシフト量に注意．
 */
q16_t q_mul(q16_t a, q16_t b) {
  /* 自分で考える */
  return 0;
}

void task2_basics(void) {
  double a_dbl = 0.3, b_dbl = 0.4;
  q16_t  a = f2q(a_dbl), b = f2q(b_dbl);
  q16_t  s = q_add(a, b);
  q16_t  p = q_mul(a, b);

  printf("--- 課題4-2: 固定小数点演算 ---\n");
  printf("a = %.6f (Q16: 0x%04X)\n", a_dbl, a);
  printf("b = %.6f (Q16: 0x%04X)\n", b_dbl, b);
  printf("[加算] a + b: 真値 = %.6f, Q16 = 0x%04X (= %.6f)\n",
         a_dbl + b_dbl, s, q2f(s));
  printf("[乗算] a * b: 真値 = %.6f, Q16 = 0x%04X (= %.6f)\n",
         a_dbl * b_dbl, p, q2f(p));
}

/*==============================================================*/
/*  立方根 LUT (Look-Up Table)                                   */
/*==============================================================*/

/*
 * LUTのエントリ数は 256 + 1 = 257．
 * cbrt_lut[i] = f2q( cbrt(i / 256.0) ),  i = 0, 1, ..., 256
 * 末尾の1個 (cbrt_lut[256]) は線形補間時の上端アクセス用．
 */
#define LUT_SIZE 257
static q16_t cbrt_lut[LUT_SIZE];

void init_cbrt_lut(void) {
  int i;
  for (i = 0; i < LUT_SIZE; ++i) {
    double x = (double)i / 256.0; /* [0, 1] を 256+1 点でサンプル */
    cbrt_lut[i] = f2q(cbrt(x));
  }
}

/*==============================================================*/
/*  課題4-3: LUTによる立方根近似 (最近傍参照)                     */
/*==============================================================*/

/*
 * cbrt_q16_nearest: Q16形式の入力 x に対して LUT 参照による cbrt(x) を返す．
 *                   x の上位 8bit を LUT インデックスとして使う．
 */
q16_t cbrt_q16_nearest(q16_t x) {
  /* 自分で考える */
  return 0;
}

void task3_lut_nearest(void) {
  printf("--- 課題4-3: cbrt LUT (最近傍参照) ---\n");
  init_cbrt_lut();
  evaluate(cbrt_q16_nearest, cbrt, "cbrt LUT 最近傍");
}

/*==============================================================*/
/*  課題4-4: LUTによる立方根近似 (線形補間)                       */
/*==============================================================*/

/*
 * cbrt_q16_linear: Q16形式の入力 x に対して LUT + 線形補間による cbrt(x) を返す．
 *
 *   idx = x の上位 8bit             (LUTインデックス, 0..255)
 *   f   = x の下位 8bit             (補間係数, 0..255)
 *   y  ≈ LUT[idx] + (LUT[idx+1] - LUT[idx]) * f / 256
 *
 * 検討事項:
 *   - 除算 /256 はシフトで置換できる．何ビットシフトか？
 *   - 中間結果の型は何にすべきか？ (.tex のヒント1, 2を参照)
 *   - 四捨五入のための加算は何の値か？ (.tex のヒント3を参照)
 */
q16_t cbrt_q16_linear(q16_t x) {
  /* 自分で考える */
  return 0;
}

void task4_lut_linear(void) {
  printf("--- 課題4-4: cbrt LUT (線形補間) ---\n");
  init_cbrt_lut();
  evaluate(cbrt_q16_linear, cbrt, "cbrt LUT 線形補間");
}

/*==============================================================*/
/*  課題4-5: 平方根 LUT (発展課題)                                */
/*==============================================================*/

static q16_t sqrt_lut[LUT_SIZE];

/*
 * init_sqrt_lut: sqrt_lut[i] = f2q( sqrt(i / 256.0) ),  i = 0, ..., 256
 *                init_cbrt_lut() を参考にすれば良い．
 */
void init_sqrt_lut(void) {
  /* 自分で考える */
}

/*
 * sqrt_q16_linear: Q16形式の入力 x に対して LUT + 線形補間による sqrt(x) を返す．
 *                  cbrt_q16_linear() とほぼ同じ構造になるはず．
 */
q16_t sqrt_q16_linear(q16_t x) {
  /* 自分で考える */
  return 0;
}

void task5_sqrt_lut(void) {
  printf("--- 課題4-5: sqrt LUT (線形補間) ---\n");
  init_sqrt_lut();
  evaluate(sqrt_q16_linear, sqrt, "sqrt LUT 線形補間");
}

/*==============================================================*/
/*  誤差評価 (実装済み)                                          */
/*==============================================================*/

/*
 * evaluate: 関数ポインタ approx の近似精度を MSE と最大誤差で評価する．
 *           Q16 形式で表現可能な全 65536 通りの入力で走査する．
 *           truefn は真値を計算する関数 (cbrt や sqrt など) を指定．
 */
void evaluate(q16_t (*approx)(q16_t), double (*truefn)(double), const char *name) {
  uint32_t i;
  double   sum_sq  = 0.0;
  double   max_err = 0.0;
  const int N = 65536;

  for (i = 0; i < (uint32_t)N; ++i) {
    q16_t  x        = (q16_t)i;
    double x_true   = q2f(x);
    double y_true   = truefn(x_true);
    double y_approx = q2f(approx(x));
    double err      = y_approx - y_true;
    if (fabs(err) > max_err) max_err = fabs(err);
    sum_sq += err * err;
  }
  printf("  [%s]\n", name);
  printf("    サンプル数 N = %d\n", N);
  printf("    MSE          = %.4e\n", sum_sq / N);
  printf("    最大絶対誤差 = %.4e\n", max_err);
}

/*==============================================================*/
/*  メニュー (実装済み)                                          */
/*==============================================================*/
int menu(void) {
  int n;
  printf("\nどの課題を実行しますか?\n");
  printf("  1: 課題4-1 (f2q, q2f の動作確認)\n");
  printf("  2: 課題4-2 (固定小数点演算 q_add, q_mul)\n");
  printf("  3: 課題4-3 (cbrt LUT 最近傍参照)\n");
  printf("  4: 課題4-4 (cbrt LUT 線形補間)\n");
  printf("  5: 課題4-5 (sqrt LUT 線形補間)\n");
  printf("  0: 終了\n");
  printf("> ");
  if (scanf("%d", &n) != 1) return 0;
  return n;
}

int main(void) {
  int n;
  do {
    n = menu();
    switch (n) {
      case 0: printf("終了します\n"); break;
      case 1: task1_warmup(); break;
      case 2: task2_basics(); break;
      case 3: task3_lut_nearest(); break;
      case 4: task4_lut_linear(); break;
      case 5: task5_sqrt_lut(); break;
      default: printf("0, 1, 2, 3, 4, 5 のいずれかを入力してください\n"); break;
    }
  } while (n != 0);
  return 0;
}
