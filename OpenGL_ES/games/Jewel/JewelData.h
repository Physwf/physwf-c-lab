#include <stdio.h>

#define JEWEL_COLOR_0 0
#define JEWEL_COLOR_1 2
#define JEWEL_COLOR_2 4
#define JEWEL_COLOR_3 8
#define JEWEL_COLOR_4 16
#define JEWEL_COLOR_5 32
#define JEWEL_COLOR_6 64

#define JEWEL_DIR_NONE 128
#define JEWEL_DIR_HERIZ 256
#define JEWEL_DIR_VERTI 512

#define JEWEL_BOMB 1024
#define JEWEL_DIAMOND 2048

#define NUM_TYPES 25
extern int* jewels;
extern int num_jewels;
extern int *offsetYs;
extern int* jewels_buffer;
extern bool updatable;

void initData();
void update(int eclipse);

bool canSwitch(int source,int target);
bool trySwitch(int source,int target);