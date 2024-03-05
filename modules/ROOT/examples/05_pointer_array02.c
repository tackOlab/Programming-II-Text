int src_data[100], dst_data[100];
int i;
int *sp, *dp;

sp = &src_data[0];
dp = &dst_data[0];

/* src_data[]の中身の定義 */

for (i = 0; i < 100; ++i) {
  *dp = *sp;
  sp++;
  dp++;
}
