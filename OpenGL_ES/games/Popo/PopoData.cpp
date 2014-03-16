#include "PopoData.h"
#include "PopoView.h"
#include "random.h"
#include <stdio.h>

popo_ptr popos;
int num_popos;

popo_t flying;
float pos[2];
float dir[2];
float speed;
bool isFlying;
float easing_target[2];
bool isEasing;

int num_rows;
int num_slots;

void initData()
{
	num_popos = 0;
	num_rows = 5;//to do: read config
	
	num_slots = (num_rows%2 == 0)?
					(num_rows)/2 * ((NUM_POPO_ROW-1)+NUM_POPO_ROW):
					(num_rows-1)/2 * ((NUM_POPO_ROW-1)+NUM_POPO_ROW) + NUM_POPO_ROW;
	popos = (popo_ptr)malloc(num_slots*sizeof(popo_t));
	int index = 0;
	for(int i=0;i<num_rows;i++)
	{
		int num;
		if(i%2==0) num = NUM_POPO_ROW;
		else num = NUM_POPO_ROW - 1;
		
		for(int j=0;j<num;j++)
		{
			popo_ptr temp = popos+index;
			index++;
			temp->row = i;
			temp->column = j;
			temp->type = rand_by_range(POPO_TYPE_NONE,POPO_TYPE_4+1);
			printf("type:%d\n",temp->type);
			
		}
	}
	
	for(int i=0;i<num_slots;i++)
	{
		popo_ptr temp = popos+i;
		// printf("type:%d,row:%d,column:%d\n",temp->type,temp->row,temp->column);
	}
	
	isFlying = false;
	isEasing = false;
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
	popo_ptr popo = popos;
	int column,row;
	int neighbor_offsets[4][2] = {{-1,0},{1,0},{-1,1},{0,1}};
	for(int i=0;i<num_slots;i++)
	{
		popo = popos+i;
		if(popo->type == POPO_TYPE_NONE) continue;
		float y = OFFSET_Y + popo->row * DIST_ROW;
		float x = (popo->row%2==0?EVEN_OFFSET_X:ODD_OFFSET_X)+DIST_COLLUM*popo->column;
		float offsetx = pos[0] - x;
		float offsety = pos[1] - y;
		if(sqrt(offsetx*offsetx + offsety*offsety)<RADIUS)
		{
			printf("collision column:%d, row:%d\n",popo->column,popo->row);
			printf("collision x:%f y:%f\n",x,y);
			printf("pos x:%f y:%f\n",pos[0],pos[1]);
			printf("offset x:%f y:%f\n",offsetx,offsety);
			row = round((pos[1]-OFFSET_Y)/DIST_ROW);
			if(row%2==0) column = round((pos[0] - EVEN_OFFSET_X)/DIST_COLLUM);
			else column = round((pos[0] - ODD_OFFSET_X)/DIST_COLLUM);
			int min = RADIUS*2;
			int minJ;
			for(int j=0;j<4;j++)
			{
				int nr = row + neighbor_offsets[j][1];
				int nc = column + neighbor_offsets[j][0];
				float nx = OFFSET_Y + (nr) * DIST_ROW;
				float ny = (nr?EVEN_OFFSET_X:ODD_OFFSET_X)+DIST_COLLUM*nc;
				float nox = pos[0] - nx;
				float noy = pos[1] - ny;
				float dist = sqrt(nox*nox+noy*noy);
				if(dist<min) 
				{
					min = dist;
					minJ = j;
				}
			}
			makeEasing(column + neighbor_offsets[minJ][0],row + neighbor_offsets[minJ][1]);
			return;
		}
		
	}
	//calculate row and column
	// flying.row = ceil((pos[1]-OFFSET_Y)/DIST_ROW);
	// if(flying.row%2 == 0)
	// {
		// flying.column = round((pos[0] - EVEN_OFFSET_X)/DIST_COLLUM);
	// }
	// else
	// {
		// flying.column = round((pos[0] - ODD_OFFSET_X)/DIST_COLLUM);
	// }
	// printf("row:%d,column%d\n",flying.row,flying.column);
	// int neighbor_offsets[6][2] = {{-1,-1},{0,-1},{-1,0},{1,0},{-1,1},{0,1}};
	// for(int i=0;i<6;i++)
	// {
		// int neighbor[2] = {neighbor_offsets[i][0]+flying.column,neighbor_offsets[i][1]+flying.row};
		// if(neighbor[0] < 0 || neighbor[1] < 0) continue;
		// for(int j=0;j<num_slots;j++)
		// {
			// popo_ptr temp = popos+j;
			// if(temp->type == POPO_TYPE_NONE) continue;
			// if(temp->row == neighbor[1] && temp->column == neighbor[0])
			// {
				// printf("xpos:%f,ypos%f\n",pos[0],pos[1]);
				// makeEasing(flying.column,flying.row);
				// isFlying = false;
				// return;
			// }
		// }
	// }
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
	flying.type = rand_by_range(POPO_TYPE_1,POPO_TYPE_4)+1;
	pos[0] = FIRE_POS_X;
	pos[1] = FIRE_POS_Y;
	dir[0] = x;
	dir[1] = y;
	speed = spd;
	printf("type:%d\n",flying.type);
	isFlying = true;
}