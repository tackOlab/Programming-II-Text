int c;
FILE *fp = fopen("myData.txt", "r");
do {
  c = getc(fp);
  printf("%c", c);
} while (c != EOF);
fclose(fp);
