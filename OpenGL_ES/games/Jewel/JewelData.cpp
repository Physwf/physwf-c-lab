#include "JewelData.h"
#include <math.h>

#define NUM_ROWS 8
#define NUM_COLS 8

typedef struct elimination_area_t {
	int type;
	int orgin;
	int num_heriz;
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
	int left_type;
	int left_index = index--;
	int left_left_index = left_index--;
	if(left_index / NUM_COLS == left_left_index / NUM_COLS)
	{
		left_type = (*(jewels+left_index) == *(jewels+left_left_index)) ? *(jewels+left_index) : 0;
	}
	//top
	int top_type;
	int top_index = index -= NUM_COLS;
	int top_top_index = index -= 2*NUM_COLS;
	if(top_index % NUM_COLS == top_top_index % NUM_COLS)
	{
		top_type = (*(jewels+top_index) == *(jewels+top_top_index)) ? *(jewels+top_index) : 0;
	}
	int type = random_by_range(JEWEL_COLOR_1,JEWEL_COLOR_6);
	while(type == left_type || type == top_type)
	{
		type = random_by_range(JEWEL_COLOR_1,JEWEL_COLOR_6);
	}
	return type;
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
	
	for(int i=0;i<num_jewels;i++)
	{
		int* jewel = jewels+i;
		int exp = getStableType(i);
		*jewel = pow(2,exp);
	}
	// updatable = false;
}

void fillEmpty()
{
	for(int i=0;i<NUM_COLS;i++)
	{
		int num_empty = 0;
		int jewels_col[NUM_ROWS] = {0};
		int num_emptys[NUM_ROWS] = {0};
		
		for(int j=NUM_ROWS-1;j>=0;j--)
		{
			int index = i + j * NUM_COLS;
			if( *(jewel+index) == 0)
			{
				num_empty ++;
			}
			else
			{
				jewels_col[j] = *(jewel+index);
			}
			num_emptys[j] = num_empty;
		}
		
		for(int j=NUM_ROWS-1;j>=0;j--)
		{
			int index = i + j * NUM_COLS;
			*(jewel+index) = (j<num_empty) ? pow(2,random_by_range(JEWEL_COLOR_1,JEWEL_COLOR_6)) :jewels_col[j];
			*(offsetYs + index) = num_emptys[j] * GIRD_SIZE;
		}
	}
}

void makeExplosion(int type, int col, int row)
{
	if(dir & JEWEL_DIR_NONE)
	{
		for(int i=-1;i<=1;i++)
		{
			for(int j=-1;j<=1;j++)
			{
				int neighbor_col = col + i;
				int neighbor_row = row + i;
				if( (neibor_col >=0 && neibor_col< NUM_COLS) && (neibor_row >=0 && neibor_row < NUM_ROWS) )
				{
					int index = neighbor_row * NUM_COLS + neighbor_col;
					*(jewel+index) = 0;
				}
			}
		}
	}
	else if(dir & JEWEL_DIR_HERIZ)
	{
		for(int i=0;i<NUM_COLS;++i)
		{
			int index = neighbor_row * NUM_COLS + i;
			*(jewel+index) = 0;
		}
	}
	else if(dir & JEWEL_DIR_VERTI)
	{
		for(int i=0;i<NUM_COLS;++i)
		{
			int index = neighbor_row * NUM_COLS + i;
			*(jewel+index) = 0;
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
		}

		if(area.num_heriz > 4 || area.num_verti > 4)//diamen
		{
			*(jewels+area.orgin) &= JEWEL_DIAMOND;
		}
		else if(area.num_heriz > 3)
		{
			*(jewels+area.orgin) &= JEWEL_BOMB;
			*(jewels+area.orgin) &= JEWEL_DIR_VERTI;
		}
		else if(area.num_verti > 3)
		{
			*(jewels+area.orgin) &= JEWEL_BOMB;
			*(jewels+area.orgin) &= JEWEL_DIR_HERIZ;
		}
		else if(area.num_heriz > 2 && area.num_verti > 2)
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
		area.type = *(jewel+i);
		area.orgin = i;
		area.num_horiz = 1;
		area.num_verti = 1;
		//right
		int right = i;
		while(right++ / 8 == row)
		{
			if(!in_horiz_flag[right])
			{
				if( *(jewel+right) == *(jewel+i)) continue;
				else break;
			}
		}
		if( right - i) > 2)
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
				if( *(jewel+down) == *(jewel+i)) continue;
				else break;
			}
		}
		if(( down - i) / 8 > 2)
		{
			for(int j=i;j<down;j+=8)
			{
				bool in_verti_flag[j] = true;
				area.num_verti ++;
				area.indices[area.num_indices] = j;
				area.num_indices ++;
			}
		}
		
		if(area.num_heriz > 2 || area.num_verti > 2) num_areas++;
	}
	
	//makeElimination(areas,num_areas);
	num_areas_out = num_areas;
	return num_areas > 0;
}

bool checkLocalElimination(int index, elim_area* area)
{
	bool in_horiz_flag[NUM_HERIZ];
	bool in_verti_flag[NUM_VERTI];
	memset(in_horiz_flag,false,sizeof(in_horiz_flag));
	memset(in_verti_flag,false,sizeof(in_verti_flag));
	//elim_area area;
	memset(area,0,sizeof(elim_area));
	int row = index / 8;
	int col = index % 8;
	area->type = *(jewel+i);
	area->orgin = index;
	area->num_horiz = 1;
	area->num_verti = 1;
	//left
	int left = index;
	while(left-- / 8 == row)
	{
		if(!in_horiz_flag[left])
		{
			if( *(jewel+left) == *(jewel+index)) continue;
			else break;
		}
	}
	if( index - left) > 2)
	{
		for(int j=index;j>left;j--)
		{
			in_horiz_flag[j] = true;
			area->num_horiz ++;
			area->indices[area->num_indices] = j;
			area->num_indices ++;
		}
	}
	//right
	int right = index;
	while(right++ / 8 == row)
	{
		if(!in_horiz_flag[right])
		{
			if( *(jewel+right) == *(jewel+index)) continue;
			else break;
		}
	}
	if( right - index) > 2)
	{
		for(int j=index;j<right;j++)
		{
			in_horiz_flag[j] = true;
			area->num_horiz ++;
			area->indices[area->num_indices] = j;
			area->num_indices ++;
		}
	}
	//up
	int up = index;
	up -= NUM_COLS;
	while(up % 8 == col)
	{
		if(!in_verti_flag[up])
		{
			if( *(jewel+up) == *(jewel+index)) continue;
			else break;
		}
	}
	if( (index - up) / 8 > 2)
	{
		for(int j=index;j>up;j-=8)
		{
			in_verti_flag[j] = true;
			area->num_verti ++;
			area->indices[area->num_indices] = j;
			area->num_indices ++;
		}
	}
	//down
	int down = index;
	down+=NUM_COLS;
	while( down % 8 == col)
	{
		if(!in_verti_flag[down])
		{
			if( *(jewel+down) == *(jewel+index)) continue;
			else break;
		}
	}
	if(( down - index) / 8 > 2)
	{
		for(int j=index;j<down;j+=8)
		{
			in_verti_flag[j] = true;
			area->num_verti ++;
			area->indices[area->num_indices] = j;
			area->num_indices ++;
		}
	}
	return area->num_indices > 0;
}

bool canSwitch(int source,int target)
{
	if(offsetYs[source] != 0 || offsetYs[target] != 0) return false;
	return true;
}

bool trySwitch(int source,int target)
{
	elim_area src_area;
	elim_area tgt_area;
	if(checkEliminationLocalized(source,&scr_area))
	{
		if(src_area.num_indices > 0)
		{
			int num_areas = 1;
			makeElimination(&scr_area,&num_areas);
		}
	}
	if(checkEliminationLocalized(target,&tgt_area))
	{
		if(tgt_area.num_indices > 0)
		{
			int num_areas = 1;
			makeElimination(&tgt_area,&num_areas);
		}
	}
	if(src_area.num_indices > 0 || tgt_area.num_indices > 0)
	{
		//fillEmpty();
		return true;
	}
	return false;
}

void rematch(int swap_times)
{
	for(int i=0;i<swap_times;i++)
	{
		int swapA = random_by_range(0,num_jewels);
		int swapB = random_by_range(0,num_jewels);
		//never mind the (swapA == swapB) situation
		int temp = *(jewel+swapA);
		*(jewel+swapA) = *(jewel+swapB);
		*(jewel+swapB) = temp;
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
			offsetYs[i] -= eclipse * 0.5;
			if(offsetYs[i] < 0) 
			{
				offsetYs[i] = 0;
				elim_area area;
				int num_area = 1;
				checkLocalElimination(i,&area);
				makeElimination(&area,&num_area);
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
