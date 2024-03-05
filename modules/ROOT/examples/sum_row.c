// 配列score[3][5]は定義されていると仮定
int i, j;
int row_sum[3];  // 行ごとの合計値を格納するための配列

// 初期化
for (i = 0; i < 3; ++i) {
  sum[i] = 0;
}

for (i = 0; i < 3; ++i) {
  for (j = 0; j < 5; ++j) {
    sum[i] += score[i][j];
  }
}
