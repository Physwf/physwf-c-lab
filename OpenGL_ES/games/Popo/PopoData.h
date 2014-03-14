#include <stdio.h>

#define NUM_POPO_ROW 10

#define POPO_TYPE_NONE 0
#define POPO_TYPE_1 1
#define POPO_TYPE_2 2
#define POPO_TYPE_3 3
#define POPO_TYPE_4 4

typedef struct popo_t
{
	int row;
	int column;
	unsigned char type;
} *popo_ptr;

extern popo_ptr popos;
extern int num_popos;
extern int num_slots;

extern float pos[2];
extern popo_t flying;
extern bool isFlying;

void initData();
void update(int eclipse);
void fire(float x,float y,float spd);