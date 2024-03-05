int i;
int data[5] = {0, 1, 2, 3, 4};
int *p_data = &data[0];

printf("data[2] = %d\n", p_data[2]);
p_data[2] = 10;
printf("data[2] = %d\n", p_data[2]);
