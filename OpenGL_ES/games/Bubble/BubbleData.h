#include <stdio.h>

#define NUM_POPO_ROW 10

#define POPO_TYPE_NONE 0
#define POPO_TYPE_1 1
#define POPO_TYPE_2 2
#define POPO_TYPE_3 3
#define POPO_TYPE_4 4

extern int* popos;
extern int num_popos;
extern int num_slots;

extern float pos[2];
extern int flying;
extern bool isFlying;
extern int waiting;

void initData();
void update(int eclipse);
int getType(int column,int row);
void fire(float x,float y,float spd);