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

void initData()
{
	int num_columns = 8;
	int num_rows = 8;
	num_jewels = num_columns * num_rows;
	jewels = (int*)malloc(num_jewels*sizeof(int));
	memset(jewels,0,num_jewels*sizeof(int));
	
	for(int i=0;i<num_jewels;i++)
	{
		int* jewel = jewels+i;
		*jewel = random_by_range(JEWEL_TYPE_1,JEWEL_TYPE_MAX);
	}
}

void checkElimination()
{
	bool in_horiz_flag[100];
	bool in_verti_flag[100];
	elim_area areas[30];
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
	
	for(int i=0;i<num_areas;i++)
	{
		elim_area area = areas[i];
		for(int j=0;j<area.num_indices;j++)
		{
			int type = *(jewels+area.indices[j]);
			//if(type == ) check bomb type
		}

		if(area.num_heriz > 4 || area.num_verti > 4)//diamen
		{
			*(jewels+area.orgin) = JEWEL_TYPE_DIAMOND;
		}
		else if(area.num_heriz > 3)
		{
			*(jewels+area.orgin) = BOMB_TYPE_V_BASE+1;
		}
		else if(area.num_verti > 3)
		{
			*(jewels+area.orgin) = BOMB_TYPE_H_BASE+1;
		}
		else if(area.num_heriz > 2 && area.num_verti > 2)
		{
			
		}
		else
		{
		}
	}
}


