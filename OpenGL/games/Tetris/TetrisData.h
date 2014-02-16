#include <stdio.h>
#include <string.h>
#include <math.h>

#define NUM_UNIT 4
#define NUM_X 10
#define NUM_Y 15
#define MAX_SQUARES (NUM_X * NUM_Y)

typedef struct square{
	int x;
	int y;
} Square;

extern Square *squares;
extern int num_squares;

void initData();
void onKeyDown(unsigned char keycode);
bool loop();

