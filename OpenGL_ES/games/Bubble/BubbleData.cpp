#include "BubbleData.h"
#include "BubbleView.h"
#include "random.h"
#include <stdio.h>

int* popos;
int num_popos;

int flying;
float pos[2];
float dir[2];
float speed;
bool isFlying;
float easing_target[2];
bool isEasing;

int num_rows;
int num_slots;

int getType(int column,int row);

void initData()
{
	num_popos = 0;
	num_rows = 7;//to do: read config
	
	num_slots = (num_rows%2 == 0)?
					(num_rows)/2 * ((NUM_POPO_ROW-1)+NUM_POPO_ROW):
					(num_rows-1)/2 * ((NUM_POPO_ROW-1)+NUM_POPO_ROW) + NUM_POPO_ROW;
	popos = (int*)malloc(num_slots*sizeof(int));
	int index = 0;
	for(int i=0;i<num_rows;i++)
	{
		int num;
		if(i%2==0) num = NUM_POPO_ROW;
		else num = NUM_POPO_ROW - 1;
		
		for(int j=0;j<num;j++)
		{
			int* temp = popos+index;
			index++;
			*temp = rand_by_range(POPO_TYPE_NONE,POPO_TYPE_4+1);
			printf("type:%d\n",*temp);
		}
	}

	isFlying = false;
	isEasing = false;
	
	printf("type:%d\n",getType(0,0));
}

int getType(int column,int row)
{
	int index;
	if(row%2==0)
	{
		index = row/2 * (2*NUM_POPO_ROW-1) + column;
	}
	else
	{
		index = (row-1)/2 * (2*NUM_POPO_ROW-1) + column + NUM_POPO_ROW;
	}
	if(index >=num_slots) return 0;
	return *(popos+index);
}

void makeEasing(int column,int row)
{
	// printf("target column:%d,target row:%d\n",column,row);
	easing_target[0] = ((row%2 == 0)?EVEN_OFFSET_X:ODD_OFFSET_X) + column * DIST_COLLUM;
	easing_target[1] = OFFSET_Y + row * DIST_ROW;
	printf("target x:%f,target y:%f\n",easing_target[0],easing_target[1]);
	
	float xOffset = easing_target[0] - pos[0];
	float yOffset = easing_target[1] - pos[1];
	float dist = sqrt(xOffset*xOffset+yOffset*yOffset);
	dir[0] = xOffset / dist;
	dir[1] = yOffset / dist;
	speed = 0.3 * dist / RADIUS;
	// easing_target[0]
	isEasing = true;
}

void checkEasing()
{
	float offsetX = easing_target[0] - pos[0];
	float offsetY = easing_target[1] - pos[1];
	// printf("offsetX:%f,offsetY:%f\n",offsetX,offsetY);
	if(offsetX*offsetX + offsetY*offsetY < 60)
	{
		pos[0] = easing_target[0];
		pos[1] = easing_target[1];
		isEasing = false;
		isFlying = false;
	}
}

void checkCollision()
{
	//check out of border
	if(pos[0]+RADIUS/2 > VIEW_W || pos[0]-RADIUS/2 < 0)
	{
		dir[0] = -dir[0];
	}
	
	int top_row = floor((pos[1]-OFFSET_Y)/DIST_ROW);
	int bottom_row = ceil((pos[1]-OFFSET_Y)/DIST_ROW);
	int even_left_column = floor((pos[0] - EVEN_OFFSET_X)/DIST_COLLUM);
	int odd_left_column = floor((pos[0] - ODD_OFFSET_X)/DIST_COLLUM);
	int even_right_column = ceil((pos[0] - EVEN_OFFSET_X)/DIST_COLLUM);
	int odd_right_column = ceil((pos[0] - ODD_OFFSET_X)/DIST_COLLUM);
	int neighbors[8]={0};
	if(top_row%2==0) {
		neighbors[0] = even_left_column;
		neighbors[1] = top_row;
		neighbors[2] = odd_left_column;
		neighbors[3] = bottom_row;
		neighbors[4] = even_right_column;
		neighbors[5] = top_row;
		neighbors[6] = odd_right_column;
		neighbors[7] = bottom_row;
	}else{
		neighbors[0] = odd_left_column;
		neighbors[1] = top_row;
		neighbors[2] = even_left_column;
		neighbors[3] = bottom_row;
		neighbors[4] = odd_right_column;
		neighbors[5] = top_row;
		neighbors[6] = even_right_column;
		neighbors[7] = bottom_row;
	}
	float min_dist = RADIUS*2;
	int I;
	bool will_collide = false;
	printf("---------------------\n");
	for(int i=0;i<4;i++)
	{
		printf("column:%d,row:%d\n",neighbors[i*2+0],neighbors[i*2+1]);
		printf("type:%d\n",getType(neighbors[i*2+0],neighbors[i*2+1]));
		//out of screen
		if(neighbors[i*2+0] < 0) continue;
		if(neighbors[i*2+1]%2==0 && neighbors[i*2+0]>=NUM_POPO_ROW) continue;
		if(neighbors[i*2+1]%2!=0 && neighbors[i*2+0]>=NUM_POPO_ROW-1) continue;
		float y = OFFSET_Y + neighbors[i*2+1] * DIST_ROW;
		float x = (neighbors[i*2+1]%2==0?EVEN_OFFSET_X:ODD_OFFSET_X)+DIST_COLLUM*neighbors[i*2+0];
		float ox = pos[0] - x;
		float oy = pos[1] - y;
		float dist = sqrt(ox*ox+oy*oy);
		if(getType(neighbors[i*2+0],neighbors[i*2+1]) == 0)
		{
			if(dist < min_dist)
			{
				min_dist = dist;
				I = i;
			}
		}
		else 
		{
			if(dist<RADIUS)
				will_collide = true;
		}
		printf(will_collide?"true\n":"false\n");
	}
	if(will_collide) {
		makeEasing(neighbors[I*2+0],neighbors[I*2+1]);
	}
}

void update(int eclipse)
{
	if(isFlying)
	{
		pos[0] += speed * dir[0] * eclipse;
		pos[1] += speed * dir[1] * eclipse;
		if(isEasing) checkEasing();
		else checkCollision();
		// printf("speed:%f,dir[0]:%f,dir[1]:%f,eclipse:%d\n",speed,dir[0],dir[1],eclipse);
	}
}

void fire(float x,float y,float spd)
{
	// printf("xdir:%f,ydir%f\n",x,y);
	srand(time(NULL));
	flying = rand_by_range(POPO_TYPE_1,POPO_TYPE_4+1)+1;
	pos[0] = FIRE_POS_X;
	pos[1] = FIRE_POS_Y;
	dir[0] = x;
	dir[1] = y;
	speed = spd;
	printf("type:%d\n",flying);
	isFlying = true;
}