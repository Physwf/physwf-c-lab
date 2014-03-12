#include <stdio.h>

#define POPO_TYPE_NONE 0
#define POPO_TYPE_1 1
#define POPO_TYPE_2 2
#define POPO_TYPE_3 3
#define POPO_TYPE_4 4

typedef struct popo_t
{
	int row;
	int collum;
	unsigned char type;
} *popo_ptr;

extern popo_ptr popos;
extern int num_popos;
extern int num_slots;

void initData();
void update();