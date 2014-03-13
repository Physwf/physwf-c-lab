#include "PopoData.h"
#include "random.h"
#include <stdio.h>



popo_ptr popos;
int num_popos;

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
			temp->type = rand_by_range(POPO_TYPE_NONE,POPO_TYPE_4);
			// printf("index:%d\n",index);
			
		}
	}
	
	for(int i=0;i<num_slots;i++)
	{
		popo_ptr temp = popos+i;
		// printf("type:%d,row:%d,column:%d\n",temp->type,temp->row,temp->column);
	}
}

