#include <stdio.h>

#define JEWEL_TYPE_1 1
#define JEWEL_TYPE_2 2
#define JEWEL_TYPE_3 3
#define JEWEL_TYPE_4 4
#define JEWEL_TYPE_MAX 5
extern int* jewels;
extern int num_jewels;

void initData();
void update(int eclipse);