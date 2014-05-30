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
	int horiz_indices[8];
	int verti_indices[8];
} elim_area, *elim_area_p;

int* jewels;
int num_jewels;
float *offsetYs;

bool updatable;



FILE* flog;

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
	int color = rand_by_range(1,JEWEL_COLOR_NUM);
	fprintf(flog,"color:%d\n",color);
	int type = (int)pow((double)2,color);
	while(type == left_type || type == top_type)
	{
		color = rand_by_range(1,JEWEL_COLOR_NUM);
		type = (int)pow((double)2,color);
	}
	printf("index:%d,type:%d,top_type:%d,left_type:%d\n",index,type,top_type,left_type);
	return color;
}

void initData()
{
	flog = fopen("jewel.log","w");
	
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
	fprintf(flog,"fillEmpty\n");
	for(int i=0;i<NUM_COLS;i++)
	{
		int num_empty = 0;
		int stack_bottom = NUM_ROWS-1;
		int jewels_col[NUM_ROWS] = {0};
		int row_col[NUM_ROWS] = {0};
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
				row_col[stack_bottom] = j;
				jewels_col[stack_bottom--] = *(jewels+index);
			}
			num_emptys[j] = num_empty;
		}
		
		for(int j=NUM_ROWS-1;j>=0;j--)
		{
			int index = i + j * NUM_COLS;
			// fprintf(flog,"fillEmpty index:%d\n",index);
			*(jewels+index) = (j<num_empty) ? (int)pow((double)2,(double)rand_by_range(1,JEWEL_COLOR_NUM)) :jewels_col[j];
			*(offsetYs + index) += j>stack_bottom ? (float)(j-row_col[j]) * GRID_SIZE:(num_empty)*GRID_SIZE;
			// if(num_empty)
				// fprintf(flog,"fillEmpty offsetY:%f\n",*(offsetYs + index));
			// if(j>stack_bottom)
				// fprintf(flog,"fillEmpty j>stack_bottom\n");
		}
	}
}

void makeExplosion(int type, int col, int row)
{
	fprintf(flog,"makeExplosion\n");
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
		fprintf(flog,"verti Explosion\n");
		for(int i=0;i<NUM_COLS;++i)
		{
			int index = col + NUM_COLS * i;
			*(jewels+index) = 0;
		}
	}
}

void checkExplosion(int *indices, int num_indices)
{
	fprintf(flog,"checkExplosion start\n");
	int origin = *(jewels+indices[0]);
	if(num_indices>2)
	{
		if(origin & JEWEL_BOMB)
		{
			int col = indices[0] % 8;
			int row = indices[0] / 8;
			makeExplosion(origin,col,row);
		}
		for(int i=1;i<num_indices;++i)
		{
			int type = *(jewels+indices[i]);
			if(type & JEWEL_BOMB)
			{
				int col = indices[i] % 8;
				int row = indices[i] / 8;
				makeExplosion(type,col,row);
			}
			else
			{
				*(jewels+indices[i]) = 0;
			}
			fprintf(flog,"index:%d\n",indices[i]);
		}
	}
}

void makeElimination(elim_area_p areas, int num_areas)
{
	fprintf(flog,"makeElimination start\n");
	for(int i=0;i<num_areas;i++)
	{
		elim_area area = areas[i];
		checkExplosion(area.horiz_indices,area.num_horiz);
		checkExplosion(area.verti_indices,area.num_verti);
		fprintf(flog,"area.num_horiz:%d\n",area.num_horiz);
		fprintf(flog,"area.num_verti:%d\n",area.num_verti);
		// *(jewels+area.orgin) = 0;
		if(area.num_horiz > 4 || area.num_verti > 4)//diamond
		{
			*(jewels+area.orgin) |= JEWEL_DIAMOND;
		}
		else if(area.num_horiz > 2 && area.num_verti > 2)
		{
			*(jewels+area.orgin) |= JEWEL_BOMB;
			*(jewels+area.orgin) |= JEWEL_DIR_NONE;
		}
		else if(area.num_horiz > 3)
		{
			*(jewels+area.orgin) |= JEWEL_BOMB;
			*(jewels+area.orgin) |= JEWEL_DIR_VERTI;
			fprintf(flog,"JEWEL_DIR_VERTI\n");
		}
		else if(area.num_verti > 3)
		{
			*(jewels+area.orgin) |= JEWEL_BOMB;
			*(jewels+area.orgin) |= JEWEL_DIR_HERIZ;
			fprintf(flog,"JEWEL_DIR_HERIZ\n");
		}
		else
		{
			*(jewels+area.orgin) = 0;
		}
		fprintf(flog,"area.orgin:%d\n",area.orgin);
	}
	//fillEmpty();
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
		area.horiz_indices[0] = area.orgin;
		area.verti_indices[0] = area.orgin;
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
				area.horiz_indices[area.num_horiz++] = j;
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
				area.verti_indices[area.num_verti++] = j;
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
	fprintf(flog,"checkLocalElimination start\n");
	bool in_horiz_flag[NUM_COLS];
	bool in_verti_flag[NUM_ROWS];
	memset(in_horiz_flag,false,sizeof(in_horiz_flag));
	memset(in_verti_flag,false,sizeof(in_verti_flag));
	//elim_area area;
	memset(area,0,sizeof(elim_area));
	int row = index / 8;
	int col = index % 8;
	int color = *(jewels+index) & COLOR_BITS;
	area->type = *(jewels+index);
	area->orgin = index;
	area->horiz_indices[0] = area->orgin;
	area->verti_indices[0] = area->orgin;
	area->num_horiz = 1;
	area->num_verti = 1;
	//left
	fprintf(flog,"index:%d\n",index);
	fprintf(flog,"left\n");
	int left = index;
	
	while((--left) / 8 == row)
	{
		fprintf(flog,"left:%d\n",left);
		fprintf(flog,"left/8:%d\n",left/8);
		
		if(!in_horiz_flag[left%NUM_ROWS])
		{
			if(*(offsetYs+left) != 0) break;
			if( *(jewels+left) & color) continue;
			else break;
		}
	}
	left++;
	if( index - left > 0)
	{
		fprintf(flog,"left > 0\n");
		for(int j=index-1;j>=left;j--)
		{
			in_horiz_flag[j%NUM_ROWS] = true;
			area->horiz_indices[area->num_horiz++] = j;
			fprintf(flog,"num_horiz:%d\n",area->num_horiz);
		}
	}
	//right
	fprintf(flog,"right\n");
	int right = index;
	fprintf(flog,"row:%d\n",row);
	while((++right) / 8 == row)
	{
		fprintf(flog,"right:%d\n",right);
		if(!in_horiz_flag[right%NUM_ROWS])
		{
			if(*(offsetYs+right) != 0) break;
			if( *(jewels+right) & color) continue;
			else break;
		}
	}
	right--;
	if( right - index > 0)
	{
		fprintf(flog,"right > 0\n");
		for(int j=index+1;j<=right;j++)
		{
			in_horiz_flag[j/NUM_COLS] = true;
			area->horiz_indices[area->num_horiz++] = j;
			fprintf(flog,"num_horiz:%d\n",area->num_horiz);
		}
	}
	//up
	fprintf(flog,"up\n");
	int up = index;
	while((up -= NUM_COLS) % 8 == col && up > 0)
	{
		fprintf(flog,"up:%d\n",up);
		if(!in_verti_flag[up/NUM_COLS])
		{
			if(*(offsetYs+up) != 0) break;
			if( *(jewels+up) & color) continue;
			else break;
		}
	}
	up+=NUM_COLS;
	fprintf(flog,"(index - up) / 8:%d\n",(index - up) / 8);
	if( (index - up) / 8 > 0)
	{
		fprintf(flog,"up > 0\n");
		for(int j=index-8;j>=up;j-=8)
		{
			in_verti_flag[j/NUM_COLS] = true;
			area->verti_indices[area->num_verti++] = j;
			fprintf(flog,"num_verti:%d\n",area->num_verti);
		}
	}
	//down
	fprintf(flog,"down\n");
	int down = index;
	while( (down+=NUM_COLS) % 8 == col && down < num_jewels)
	{
		fprintf(flog,"down:%d\n",down);
		if(!in_verti_flag[down/NUM_COLS])
		{
			if(*(offsetYs+down) != 0) break;
			if( *(jewels+down) & color) continue;
			else break;
		}
	}
	down -= NUM_COLS;
	fprintf(flog,"( down - index) / 8:%d\n",( down - index) / 8);
	if(( down - index) / 8 > 0)
	{
		fprintf(flog,"down > 0\n");
		for(int j=index+8;j<=down;j+=8)
		{
			in_verti_flag[j/NUM_COLS] = true;
			area->verti_indices[area->num_verti++] = j;
			fprintf(flog,"num_verti:%d\n",area->num_verti);
		}
	}
	fprintf(flog,"num_horiz:%d,num_verti:%d\n",area->num_horiz,area->num_verti);
	fprintf(flog,"checkLocalElimination end\n");
	return area->num_horiz > 2 || area->num_verti > 2;
}

bool canSwitch(int positive,int passive)
{
	// fprintf(flog,"canSwtich\n");
	// fprintf(flog,"offsetYs[positive]:%f\n",offsetYs[positive]);
	// fprintf(flog,"positive:%d\n",positive);
	// fprintf(flog,"positive col:%d\n",positive % NUM_COLS);
	// fprintf(flog,"positive offsetYs[col]:%f\n",offsetYs[positive % NUM_COLS]);
	// fprintf(flog,"passive:%d\n",passive);
	// fprintf(flog,"passive col:%d\n",passive % NUM_COLS);
	// fprintf(flog,"offsetYs[passive]:%f\n",offsetYs[passive]);
	// fprintf(flog,"passive offsetYs[col]:%f\n",offsetYs[passive % NUM_COLS]);
	if(offsetYs[positive] != 0) return false;
	int col = positive % NUM_COLS;
	if(offsetYs[col] != 0) return false;
	if(offsetYs[passive] != 0) return false;
	col = passive % NUM_COLS;
	if(offsetYs[col] != 0) return false;
	return true;
}

bool trySwitch(int source,int target)
{
	elim_area src_area = {0,0,0,0,{0},{0}};
	elim_area tgt_area = {0,0,0,0,{0},{0}};
	fprintf(flog,"trySwitch start--------------------\n");
	if(checkLocalElimination(source,&src_area))
	{
		fprintf(flog,"checkLocalElimination source\n");
		if(src_area.num_horiz > 2 || src_area.num_verti > 2)
		{
			fprintf(flog,"makeElimination start\n");
			int num_areas = 1;
			makeElimination(&src_area,num_areas);
		}
	}
	if(checkLocalElimination(target,&tgt_area))
	{
		fprintf(flog,"checkLocalElimination target\n");
		if(tgt_area.num_horiz > 2 || tgt_area.num_verti > 2)
		{
			fprintf(flog,"makeElimination start\n");
			int num_areas = 1;
			makeElimination(&tgt_area,num_areas);
		}
	}
	fillEmpty();
	fprintf(flog,"trySwitch end--------------------\n");
	return src_area.num_horiz > 2 || src_area.num_verti > 2 || tgt_area.num_horiz > 2 || tgt_area.num_verti > 2;
}

void rematch(int swap_times)
{
	for(int i=0;i<swap_times;i++)
	{
		int swapA = rand_by_range(1,num_jewels);
		int swapB = rand_by_range(1,num_jewels);
		//never mind the (swapA == swapB) situation
		int temp = *(jewels+swapA);
		*(jewels+swapA) = *(jewels+swapB);
		*(jewels+swapB) = temp;
	}
}


void update(int eclipse)
{
	bool ready = true;
	bool hasElimination = false;
	for(int i=0;i<num_jewels;i++)
	{
		if(offsetYs[i] == 0) continue;
		else
		{
			//fprintf(flog,"offsetYs[i]:%f\n",offsetYs[i]);
			//fprintf(flog,"eclipse * 0.5:%f\n",eclipse * 0.5);
			offsetYs[i] -= eclipse * 0.1;
			//fprintf(flog,"offsetYs[i]:%f\n",offsetYs[i]);
			if(offsetYs[i] < 0) 
			{
				// fprintf(flog,"offsetYs[i] < 0\n");
				offsetYs[i] = 0;
				elim_area area;
				int num_area = 1;
				// fprintf(flog,"checkLocalElimination,i:%d\n",i);
				if(checkLocalElimination(i,&area))
				{
					makeElimination(&area,num_area);
					hasElimination = true;
				}
			}
			ready = false;
		}
	}
	if(hasElimination)
	{
		fillEmpty();
	}
	
	if(ready)
	{
		// check match
		// rematch(swap_times+=5);
	}
}
