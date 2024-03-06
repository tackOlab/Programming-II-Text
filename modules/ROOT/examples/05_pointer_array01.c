int data[100];
int i;
int *p_data, *p;

p_data = &data[0];
p = p_data; // <1>

for (i = 0; i < 100; ++i) {
  *p++ = 0;
}
