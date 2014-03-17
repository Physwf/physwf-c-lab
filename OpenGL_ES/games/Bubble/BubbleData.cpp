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
int target_slot[2];
bool isEasing;

int num_bubble_rows;
int num_empty_rows;
int num_total_rows;
int num_slots;

int getType(int column,int row);

void initData()
{
	num_popos = 0;
	num_bubble_rows = 7;//to do: read config
	num_empty_rows = 7;
	num_total_rows = num_bubble_rows + num_empty_rows;
	
	num_slots = (num_total_rows%2 == 0)?
					(num_total_rows)/2 * ((NUM_POPO_ROW-1)+NUM_POPO_ROW):
					(num_total_rows-1)/2 * ((NUM_POPO_ROW-1)+NUM_POPO_ROW) + NUM_POPO_ROW;
	popos = (int*)malloc(num_slots*sizeof(int));
	int index = 0;
	int num;
	int i=0;
	for(;i<num_bubble_rows;i++)
	{
		
		if(i%2==0) num = NUM_POPO_ROW;
		else num = NUM_POPO_ROW - 1;
		
		for(int j=0;j<num;j++)
		{
			int* temp = popos+index;
			index++;
			*temp = rand_by_range(POPO_TYPE_NONE,POPO_TYPE_4+1);
			// printf("type:%d\n",*temp);
		}
	}
	//empty rows
	for(;i<num_total_rows;i++)
	{
		if(i%2==0) num = NUM_POPO_ROW;
		else num = NUM_POPO_ROW - 1;
		
		for(int j=0;j<num;j++)
		{
			int* temp = popos+index;
			index++;
			*temp = POPO_TYPE_NONE;
		}
	}
	isFlying = false;
	isEasing = false;
	
}

int getIndex(int column,int row)
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
	return index;
}

int getType(int column,int row)
{
	int index = getIndex(column,row);
	if(index >=num_slots) return 0;
	return *(popos+index);
}

const int MAX_ELEMIN = 100;
int elemin_list[MAX_ELEMIN];
int num_elemin;
int elemin_type;

int check_list[MAX_ELEMIN];
int num_check;

int isolated_list[MAX_ELEMIN];
int num_isolated;

bool checkIsolated(int column,int row)
{
	if(row==0) return false;
	int top_left,top_right;
	
	if(row%2==0)
	{
		top_left = column-1;
		top_right = column;
	}
	else
	{
		top_left = column;
		top_right = column+1;
	}
	int top = row - 1;
	if(top%2 == 0)
	{
		if(top_left>=0 && top_left<NUM_POPO_ROW)
			return checkIsolated(top_left,row-1);
		if(top_right>=0 && top_right<NUM_POPO_ROW)
			return checkIsolated(top_right,row-1);
	}
	else
	{
		if(top_left>=0 && top_left<NUM_POPO_ROW-1)
			return checkIsolated(top_left,row-1);
		if(top_right>=0 && top_right<NUM_POPO_ROW-1)
			return checkIsolated(top_right,row-1);
	}
	return true;
}

void checkElemination(int column,int row)
{
	if(column < 0) return;
	if(row%2==0 && column>= NUM_POPO_ROW) return;
	if(row%2!=0 && column>= NUM_POPO_ROW-1) return;
	
	if(row < 0) return;
	if(row >= num_total_rows) return;

	
	int index = getIndex(column,row);
	for(int i=0;i<num_check;i++)
	{
		if(check_list[i] == index) return;
	}
	check_list[num_check++]=index;
	
	if(*(popos+index) != elemin_type && *(popos+index) != POPO_TYPE_NONE) return;
	elemin_list[num_elemin++] = index;
	
	printf("elemin,column:%d,row:%d\n",column,row);
	printf("num_elemin:%d\n",num_elemin);
	int diff_left,diff_right;
	int same_left,same_right;
	if(row%2==0)
	{
		diff_left = column-1;
		diff_right = column;
	}
	else
	{
		diff_left = column;
		diff_right = column+1;
	}
	int neighbors[12]={
				diff_left,row-1,diff_right,row-1,
				column - 1,row,column+1,row,
				diff_left,row+1,diff_right,row+1
				};
	for(int i=0;i<6;i++)
	{
		// index = getIndex(neighbors[i*2+0],neighbors[i*2+1]);
		checkElemination(neighbors[i*2+0],neighbors[i*2+1]);
	}
	
}

void makeEasing(int column,int row)
{
	// printf("target column:%d,target row:%d\n",column,row);
	target_slot[0] = column;
	target_slot[1] = row;
	easing_target[0] = ((row%2 == 0)?EVEN_OFFSET_X:ODD_OFFSET_X) + column * DIST_COLLUM;
	easing_target[1] = OFFSET_Y + row * DIST_ROW;
	// printf("target x:%f,target y:%f\n",easing_target[0],easing_target[1]);
	
	float xOffset = easing_target[0] - pos[0];
	float yOffset = easing_target[1] - pos[1];
	float dist = sqrt(xOffset*xOffset+yOffset*yOffset);
	dir[0] = xOffset / dist;
	dir[1] = yOffset / dist;
	speed = 0.3 * dist / RADIUS;
	// easing_target[0]
	isEasing = true;
}

void makeElemination()
{
	if(num_elemin>2)
	{
		for(int i=0;i<num_elemin;i++)
		{
			printf("eleminate\n");
			printf("index:%d\n",elemin_list[i]);
			*(popos+elemin_list[i]) = POPO_TYPE_NONE;
		}
	}
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
		int index = getIndex(target_slot[0],target_slot[1]);
		*(popos+index) = flying;
		printf("target index:%d\n",index);
		elemin_type = flying;
		num_elemin = 0;
		num_check = 0;
		// num_isolated = 0;
		checkElemination(target_slot[0],target_slot[1]);
		makeElemination();
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
	// printf("---------------------\n");
	for(int i=0;i<4;i++)
	{
		// printf("column:%d,row:%d\n",neighbors[i*2+0],neighbors[i*2+1]);
		// printf("type:%d\n",getType(neighbors[i*2+0],neighbors[i*2+1]));
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
		// printf(will_collide?"true\n":"false\n");
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