#include <stdio.h>

#define JEWEL_TYPE_1 1
#define JEWEL_TYPE_2 2
#define JEWEL_TYPE_3 3
#define JEWEL_TYPE_4 4
#define JEWEL_TYPE_5 5
#define JEWEL_TYPE_6 6

#define BOMB_TYPE_V_BASE 6
#define BOMB_TYPE_1_H 7
#define BOMB_TYPE_2_H 8
#define BOMB_TYPE_3_H 9
#define BOMB_TYPE_4_H 10
#define BOMB_TYPE_5_H 11
#define BOMB_TYPE_6_H 12

#define BOMB_TYPE_H_BASE 12
#define BOMB_TYPE_1_V 13
#define BOMB_TYPE_2_V 14
#define BOMB_TYPE_3_V 15
#define BOMB_TYPE_4_V 16
#define BOMB_TYPE_5_V 17
#define BOMB_TYPE_6_V 18

#define BOMB_TYPE_BASE 18
#define BOMB_TYPE_1_V 19
#define BOMB_TYPE_2_V 20
#define BOMB_TYPE_3_V 21
#define BOMB_TYPE_4_V 22
#define BOMB_TYPE_5_V 23
#define BOMB_TYPE_6_V 24

#define JEWEL_TYPE_DIAMOND 25

extern int* jewels;
extern int num_jewels;

void initData();
void update(int eclipse);