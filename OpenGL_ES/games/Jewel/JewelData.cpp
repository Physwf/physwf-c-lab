#include "JewelData.h"
#include "JewelView.h"
#include <math.h>
#include <string.h>
#include <random.h>

typedef struct elimination_area_t {
	int type;
	int orgin;
	int num_horiz;
	int num_verti;
	int indices[100];
	int num_indices;
} elim_area, *elim_area_p;

int* jewels;
int num_jewels;
float *offsetYs;

bool updatable;

int getStableType(int index)
{
	//left
	int left_type =-1;
	int left_index = index-1;
	int left_left_index = left_index-1;
	if(left_index / NUM_COLS == left_left_index / NUM_COLS && left_left_index>=0)
	{
		left_type = (*(jewels+left_index) == *(jewels+left_left_index)) ? *(jewels+left_index) : -2;
	}
	//top
	int top_type=-1;
	int top_index = (index - NUM_COLS);
	int top_top_index = (index - 2*NUM_COLS);
	if( (top_index % NUM_COLS) == (top_top_index % NUM_COLS) && top_top_index >= 0 )
	{
		top_type = (*(jewels+top_index) == *(jewels+top_top_index)) ? *(jewels+top_index) : -3;
	}
	int color = rand_by_range(0,JEWEL_COLOR_NUM);
	int type = (int)pow((double)2,color);
	while(type == left_type || type == top_type)
	{
		color = rand_by_range(0,JEWEL_COLOR_NUM);
		type = (int)pow((double)2,color);
	}
	printf("index:%d,type:%d,top_type:%d,left_type:%d\n",index,type,top_type,left_type);
	return color;
}

void initData()
{
	int num_columns = 8;
	int num_rows = 8;
	num_jewels = num_columns * num_rows;
	
	jewels = (int*)malloc(num_jewels*sizeof(int));
	memset(jewels,0,num_jewels*sizeof(int));
	
	offsetYs = (float*)malloc(num_jewels*sizeof(float));
	memset(offsetYs,0,num_jewels*sizeof(float));
	
	// srand(time(NULL));
	for(int i=0;i<num_jewels;i++)
	{
		int* jewel = jewels+i;
		int exp = getStableType(i);
		// printf("exp:%d\n",exp);
		*jewel = (int)pow((double)2,(double)exp);
	}
	// updatable = false;
}

void fillEmpty()
{
	for(int i=0;i<NUM_COLS;i++)
	{
		int num_empty = 0;
		int stack_bottom = NUM_ROWS-1;
		int jewels_col[NUM_ROWS] = {0};
		int num_emptys[NUM_ROWS] = {0};
		
		for(int j=NUM_ROWS-1;j>=0;j--)
		{
			int index = i + j * NUM_COLS;
			if( *(jewels+index) == 0)
			{
				num_empty ++;
			}
			else
			{
				jewels_col[stack_bottom--] = *(jewels+index);
			}
			num_emptys[j] = num_empty;
		}
		
		for(int j=NUM_ROWS-1;j>=0;j--)
		{
			int index = i + j * NUM_COLS;
			*(jewels+index) = (j<num_empty) ? (int)pow((double)2,(double)rand_by_range(0,JEWEL_COLOR_NUM)) :jewels_col[j];
			*(offsetYs + index) = num_emptys[j] * GRID_SIZE;
		}
	}
}

void makeExplosion(int type, int col, int row)
{
	if(type & JEWEL_DIR_NONE)
	{
		for(int i=-1;i<=1;i++)
		{
			for(int j=-1;j<=1;j++)
			{
				int neighbor_col = col + i;
				int neighbor_row = row + i;
				if( (neighbor_col >=0 && neighbor_col< NUM_COLS) && (neighbor_row >=0 && neighbor_row < NUM_ROWS) )
				{
					int index = neighbor_row * NUM_COLS + neighbor_col;
					*(jewels+index) = 0;
				}
			}
		}
	}
	else if(type & JEWEL_DIR_HERIZ)
	{
		for(int i=0;i<NUM_COLS;++i)
		{
			int index = row * NUM_COLS + i;
			*(jewels+index) = 0;
		}
	}
	else if(type & JEWEL_DIR_VERTI)
	{
		for(int i=0;i<NUM_COLS;++i)
		{
			int index = col * NUM_COLS * i;
			*(jewels+index) = 0;
		}
	}
}

void makeElimination(elim_area_p areas, int num_areas)
{
	for(int i=0;i<num_areas;i++)
	{
		elim_area area = areas[i];
		for(int j=0;j<area.num_indices;j++)
		{
			int type = *(jewels+area.indices[j]);
			if(type & JEWEL_BOMB)
			{
				int col = area.indices[j] % 8;
				int row = area.indices[j] / 8;
				makeExplosion(type,col,row);
			}
			*(jewels+area.indices[j]) = 0;
			*(jewels+area.orgin) = 0;
		}

		if(area.num_horiz > 4 || area.num_verti > 4)//diamond
		{
			*(jewels+area.orgin) &= JEWEL_DIAMOND;
		}
		else if(area.num_horiz > 3)
		{
			*(jewels+area.orgin) &= JEWEL_BOMB;
			*(jewels+area.orgin) &= JEWEL_DIR_VERTI;
		}
		else if(area.num_verti > 3)
		{
			*(jewels+area.orgin) &= JEWEL_BOMB;
			*(jewels+area.orgin) &= JEWEL_DIR_HERIZ;
		}
		else if(area.num_horiz > 2 && area.num_verti > 2)
		{
			*(jewels+area.orgin) &= JEWEL_BOMB;
			*(jewels+area.orgin) &= JEWEL_DIR_NONE;
		}
		else
		{
			// do noting;
		}
	}
	fillEmpty();
}

bool checkGlobalElimination(elim_area_p areas, int* num_areas_out)
{
	bool in_horiz_flag[100];
	bool in_verti_flag[100];
	memset(in_horiz_flag,false,sizeof(in_horiz_flag));
	memset(in_verti_flag,false,sizeof(in_verti_flag));
	//elim_area areas[30];
	memset(areas,0,sizeof(areas));
	int num_areas = 0;
	for(int i=0;i<num_jewels;i++)
	{
		int row = i / 8;
		int col = i % 8;
		elim_area area = areas[num_areas];
		area.type = *(jewels+i);
		area.orgin = i;
		area.num_horiz = 1;
		area.num_verti = 1;
		//right
		int right = i;
		while(right++ / 8 == row)
		{
			if(!in_horiz_flag[right])
			{
				if( *(jewels+right) == *(jewels+i)) continue;
				else break;
			}
		}
		if( right - i > 2)
		{
			for(int j=i;j<right;j++)
			{
				in_horiz_flag[j] = true;
				area.num_horiz ++;
				area.indices[area.num_indices] = j;
				area.num_indices ++;
			}
		}
		//down
		int down = i;
		down+=NUM_COLS;
		while( down % 8 == col)
		{
			if(!in_verti_flag[down])
			{
				if( *(jewels+down) == *(jewels+i)) continue;
				else break;
			}
		}
		if(( down - i) / 8 > 2)
		{
			for(int j=i;j<down;j+=8)
			{
				in_verti_flag[j] = true;
				area.num_verti ++;
				area.indices[area.num_indices] = j;
				area.num_indices ++;
			}
		}
		
		if(area.num_horiz > 2 || area.num_verti > 2) num_areas++;
	}
	
	//makeElimination(areas,num_areas);
	*num_areas_out = num_areas;
	return num_areas > 0;
}

bool checkLocalElimination(const int index, elim_area* area)
{
	printf("checkLocalElimination start\n");
	bool in_horiz_flag[NUM_COLS];
	bool in_verti_flag[NUM_ROWS];
	memset(in_horiz_flag,false,sizeof(in_horiz_flag));
	memset(in_verti_flag,false,sizeof(in_verti_flag));
	//elim_area area;
	memset(area,0,sizeof(elim_area));
	int row = index / 8;
	int col = index % 8;
	area->type = *(jewels+index);
	area->orgin = index;
	area->num_horiz = 1;
	area->num_verti = 1;
	//left
	printf("index:%d\n",index);
	printf("left\n");
	int left = index;
	
	while((left--) / 8 == row)
	{
		printf("left:%d\n",left);
		printf("left/8:%d\n",left/8);
		
		if(!in_horiz_flag[left%NUM_ROWS])
		{
			if( *(jewels+left) == *(jewels+index)) continue;
			else break;
		}
	}
	left++;
	if( index - left > 0)
	{
		printf("left > 0\n");
		for(int j=index-1;j>=left;j--)
		{
			in_horiz_flag[j%NUM_ROWS] = true;
			area->num_horiz ++;
			printf("num_horiz:%d\n",area->num_horiz);
			area->indices[area->num_indices] = j;
			area->num_indices ++;
		}
	}
	//right
	printf("right\n");
	int right = index;
	while((right++) / 8 == row)
	{
		printf("right:%d\n",right);
		if(!in_horiz_flag[right%NUM_ROWS])
		{
			if( *(jewels+right) == *(jewels+index)) continue;
			else break;
		}
	}
	right--;
	if( right - index > 0)
	{
		printf("right > 0\n");
		for(int j=index+1;j<=right;j++)
		{
			in_horiz_flag[j/NUM_COLS] = true;
			area->num_horiz ++;
			printf("num_horiz:%d\n",area->num_horiz);
			area->indices[area->num_indices] = j;
			area->num_indices ++;
		}
	}
	//up
	printf("up\n");
	int up = index;
	while((up -= NUM_COLS) % 8 == col && up > 0)
	{
		printf("up:%d\n",up);
		if(!in_verti_flag[up/NUM_COLS])
		{
			if( *(jewels+up) == *(jewels+index)) continue;
			else break;
		}
	}
	up+=NUM_COLS;
	printf("(index - up) / 8:%d\n",(index - up) / 8);
	if( (index - up) / 8 > 0)
	{
		printf("up > 0\n");
		for(int j=index-8;j>=up;j-=8)
		{
			in_verti_flag[j/NUM_COLS] = true;
			area->num_verti ++;
			printf("num_verti:%d\n",area->num_verti);
			area->indices[area->num_indices] = j;
			area->num_indices ++;
		}
	}
	//down
	printf("down\n");
	int down = index;
	while( (down+=NUM_COLS) % 8 == col && down < num_jewels)
	{
		printf("down:%d\n",down);
		if(!in_verti_flag[down/NUM_COLS])
		{
			if( *(jewels+down) == *(jewels+index)) continue;
			else break;
		}
	}
	down -= NUM_COLS;
	printf("( down - index) / 8:%d\n",( down - index) / 8);
	if(( down - index) / 8 > 0)
	{
		printf("down > 0\n");
		for(int j=index+8;j<=down;j+=8)
		{
			in_verti_flag[j/NUM_COLS] = true;
			area->num_verti ++;
			printf("num_verti:%d\n",area->num_verti);
			area->indices[area->num_indices] = j;
			area->num_indices ++;
		}
	}
	printf("num_horiz:%d,num_verti:%d\n",area->num_horiz,area->num_verti);
	printf("checkLocalElimination end\n");
	return area->num_horiz > 2 || area->num_verti > 2;
}

bool canSwitch(int source,int target)
{
	if(offsetYs[source] != 0 || offsetYs[target] != 0) return false;
	return true;
}

bool trySwitch(int source,int target)
{
	elim_area src_area = {0,0,0,0,{0},0};
	elim_area tgt_area = {0,0,0,0,{0},0};
	printf("trySwitch start--------------------\n");
	if(checkLocalElimination(source,&src_area))
	{
		printf("checkLocalElimination source\n");
		if(src_area.num_indices > 0)
		{
			printf("makeElimination start\n");
			int num_areas = 1;
			makeElimination(&src_area,num_areas);
		}
	}
	if(checkLocalElimination(target,&tgt_area))
	{
		printf("checkLocalElimination target\n");
		if(tgt_area.num_indices > 0)
		{
			printf("makeElimination start\n");
			int num_areas = 1;
			makeElimination(&tgt_area,num_areas);
		}
	}
	printf("trySwitch end--------------------\n");
	return src_area.num_horiz > 2 || src_area.num_verti > 2 || tgt_area.num_horiz > 2 || tgt_area.num_verti > 2;
}

void rematch(int swap_times)
{
	for(int i=0;i<swap_times;i++)
	{
		int swapA = rand_by_range(0,num_jewels);
		int swapB = rand_by_range(0,num_jewels);
		//never mind the (swapA == swapB) situation
		int temp = *(jewels+swapA);
		*(jewels+swapA) = *(jewels+swapB);
		*(jewels+swapB) = temp;
	}
}


void update(int eclipse)
{
	bool ready = true;
	for(int i=0;i<num_jewels;i++)
	{
		if(offsetYs[i] == 0) continue;
		else
		{
			//printf("offsetYs[i]:%f\n",offsetYs[i]);
			//printf("eclipse * 0.5:%f\n",eclipse * 0.5);
			offsetYs[i] -= eclipse * 0.01;
			//printf("offsetYs[i]:%f\n",offsetYs[i]);
			if(offsetYs[i] < 0) 
			{
				printf("offsetYs[i] < 0\n");
				offsetYs[i] = 0;
				elim_area area;
				int num_area = 1;
				printf("checkLocalElimination,i:%d\n",i);
				if(checkLocalElimination(i,&area))
				{
					makeElimination(&area,num_area);
				}
			}
			ready = false;
		}
	}
	if(ready)
	{
		// check match
		// rematch(swap_times+=5);
	}
}
