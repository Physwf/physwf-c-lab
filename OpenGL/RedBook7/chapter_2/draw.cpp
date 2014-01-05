#include <stdlib.h>
#include "draw.h"
#include <time.h>

int rand_by_range(int min,int max)
{
	return rand() % (max-min) + min;
}

void drawPoints()
{
	srand(time(NULL));
	glBegin(GL_POINTS);
		for(int i=0;i<10;i++)
		{
			int x = rand_by_range(0,STAGE_WIDTH);
			int y = rand_by_range(0,STAGE_HEIGHT);
			glVertex2i(x,y);
		}
	glEnd();
}