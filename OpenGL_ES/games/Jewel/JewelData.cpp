#include "JewelData.h"

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
	int checked_list[100];
	int num_checked = 0;
}
