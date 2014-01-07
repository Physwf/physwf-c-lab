#include "random.h"
#include "draw.h"

void drawPoints()
{
	srand(time(NULL));
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	int numPoints = 5;
	int vertices[2*5];
	float colors[3*5];
	
	for(int i=0;i<5;i++)
	{
		vertices[2*i] = rand_by_range(0,STAGE_WIDTH);
		vertices[2*i+1] = rand_by_range(0,STAGE_HEIGHT);
		
		colors[3*i] = random();
		colors[3*i+1] = random();
		colors[3*i+2] = random();
	}
	
	glColorPointer(3,GL_FLOAT,0,colors);
	glVertexPointer(2,GL_INT,0,vertices);
	
	glBegin(GL_POINTS);
		for(int i=0;i<5;i++)
		{
			glArrayElement(i);
		}
	glEnd();
}

