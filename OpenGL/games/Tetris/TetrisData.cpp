#include "TetrisData.h"
#include "random.h"

#define KEY_LEFT 100
#define KEY_UP 101
#define KEY_RIGHT 102
#define KEY_DOWN 103

int num_squares;
Square *squares;

Square *moving_squares;
Square *still_squares;
int num_still_squares;

FILE *log_file;

int* getNodes()
{
	int dirs[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
	int candi_nodes[10*2];
	int num_candi_nodes = 0;
	int* rslt_nodes = (int*)calloc(NUM_UNIT*2,sizeof(int));
	int num_rslt_nodes = 1;
	int new_node[2] = {0,0};
	int test_node[2] = {0,0};
	for(int k=0;k<3;k++)
	{
		for(int i=0;i<NUM_UNIT;i++)
		{
			bool flag = false;
			test_node[0] = new_node[0]+ dirs[i][0];
			test_node[1] = new_node[1]+ dirs[i][1];
			for(int j=0;j<num_rslt_nodes;j++)
			{
				if(test_node[0] == rslt_nodes[j*2+0] && test_node[1] == rslt_nodes[j*2+1])
				{
					flag = true;
					break;
				}
			}
			for(int j=0;j<num_candi_nodes;j++)
			{
				if(flag) break;
				if(test_node[0] == candi_nodes[j*2+0] && test_node[1] == candi_nodes[j*2+1])
				{
					flag = true;
					break;
				}
			}
			if(flag) continue;
			candi_nodes[num_candi_nodes*2+0] = test_node[0];
			candi_nodes[num_candi_nodes*2+1] = test_node[1];
			num_candi_nodes++;
		}
		fprintf(log_file,"-----------------------\n");
		for(int j=0;j<num_candi_nodes;j++)
		{
			fprintf(log_file,"cand:x:%d,y:%d\n",candi_nodes[j*2+0],candi_nodes[j*2+1]);
		}
		fprintf(log_file,"*********\n");
		int rad = rand_by_range(0,num_candi_nodes);
		fprintf(log_file,"rad:%d\n",rad);
		new_node[0] = rslt_nodes[num_rslt_nodes*2+0] = candi_nodes[rad*2+0];
		new_node[1] = rslt_nodes[num_rslt_nodes*2+1] = candi_nodes[rad*2+1];
		num_rslt_nodes++;
		memcpy(candi_nodes+rad*2,candi_nodes+rad*2+2,(num_candi_nodes-rad-1)*2*sizeof(int));
		num_candi_nodes--;
		for(int j=0;j<num_candi_nodes;j++)
		{
			fprintf(log_file,"cand:x:%d,y:%d\n",candi_nodes[j*2+0],candi_nodes[j*2+1]);
		}
		fprintf(log_file,"-----------------------\n");
		
	}
	return rslt_nodes;
}

Square* getNext()
{
	Square* next = (Square*) calloc(NUM_UNIT,sizeof(Square));
	
	int *nodes = getNodes();
	int l=100;int r=-100;
	for(int i=0;i<NUM_UNIT;i++)
	{
		if(nodes[2*i+0] <l) l = nodes[2*i+0];
		if(nodes[2*i+0] >r) r = nodes[2*i+0];
	}
	int cen_x = (NUM_X - (r-l))/2;
	
	for(int i=0;i<NUM_UNIT;i++)
	{
		((Square*)(next+i))->x = nodes[i*2+0]+cen_x;
		((Square*)(next+i))->y = nodes[i*2+1];
	}
	return next;
}

void initData()
{
	log_file = fopen("log_tetris.log","w");
	
	srand(time(NULL));
	
	squares = (Square*) calloc(MAX_SQUARES,sizeof(Square));
	
	still_squares = (Square*) calloc(MAX_SQUARES,sizeof(Square));
	num_still_squares = 0;
	
	moving_squares = getNext();
	num_squares = NUM_UNIT;
}

bool checkCollision(int dirX,int dirY)
{
	for(int i=0;i<num_still_squares;i++)
	{
		for(int j=0;j<NUM_UNIT;j++)
		{
			if(still_squares[i].x == moving_squares[j].x+dirX && still_squares[i].y == moving_squares[j].y+dirY)
				return true;
		}
	}
	return false;
}

bool checkLeft()
{
	for(int i=0;i<NUM_UNIT;i++)
	{
		if(moving_squares[i].x == 0)
			return true;
	}
	return false;
}

bool checkRight()
{
	for(int i=0;i<NUM_UNIT;i++)
	{
		if(moving_squares[i].x == NUM_X-1)
			return true;
	}
	return false;
}

bool checkBottom()
{
	for(int i=0;i<NUM_UNIT;i++)
	{
		if(moving_squares[i].y == NUM_Y-1)
			return true;
	}
	return false;
}

void rotate()
{
	int l=100,r=-100;
	int t=100,b=-100;
	for(int i=0;i<NUM_UNIT;i++)
	{
		if(moving_squares[i].x > r) r = moving_squares[i].x;
		if(moving_squares[i].x < l) l = moving_squares[i].x;
		if(moving_squares[i].y > b) b = moving_squares[i].y;
		if(moving_squares[i].y < t) t = moving_squares[i].y;
	}
	int org_x = 100;
	int org_y = 100;
	for(int i=0;i<NUM_UNIT;i++)
	{
		if(moving_squares[i].x < org_x)
			org_x = moving_squares[i].x;
		if(moving_squares[i].y < org_y)
			org_y = moving_squares[i].y;
	}
	int center_x = (r - l) / 2;
	int center_y = (b - t) / 2;
	/* rotate matrix
	|0  1|
	|-1 0|
	*/
	Square test_squares[NUM_UNIT];
	
	for(int i=0;i<NUM_UNIT;i++)
	{
		int x = (moving_squares[i].y - center_y - org_y) * (-1);
		int y = (moving_squares[i].x - center_x - org_x) * (1);
		
		//check collision and bottom
		for(int j=0;j<num_still_squares;j++)
		{
			if(x == still_squares[j].x && y == still_squares[j].y) 
			{
				printf("collision\n");
				return;
			}
			if(y>=NUM_Y) return;
		}
		
		test_squares[i].x = x + org_x + center_x;
		test_squares[i].y = y + org_y + center_y;
	}
	//check out of boarder
	l=100;r=-100;
	t=100;b=-100;
	for(int i=0;i<NUM_UNIT;i++)	
	{
		if(test_squares[i].x < l) l = test_squares[i].x;
		if(test_squares[i].y > r) r = test_squares[i].x;
	}
	int offset=0;
	if(l<0) offset = l;
	if(r>=NUM_X) offset = r - NUM_X+1;
	int test_x[NUM_UNIT];
	for(int i=0;i<NUM_UNIT;i++)
	{
		test_x[i] = test_squares[i].x - offset;
		for(int j=0;j<num_still_squares;j++)
		{
			if(test_x[i] == still_squares[j].x && test_squares[i].y == still_squares[j].y) return;
		}
	}
	for(int i=0;i<NUM_UNIT;i++)
	{
		moving_squares[i].x = test_x[i];
		moving_squares[i].y = test_squares[i].y;
	}
}

void translate(char dir)
{
	// printf("translate:%c\n",dir);
	if(dir == 'L')
	{
		if(!checkLeft() && !checkCollision(-1,0)) 
		{
			for(int i=0;i<NUM_UNIT;i++)
				moving_squares[i].x--;
		}
	}
	else if(dir == 'R')
	{
		if(!checkRight() && !checkCollision(1,0)) 
		{
			for(int i=0;i<NUM_UNIT;i++)
				moving_squares[i].x++;
		}
	}
}

void drop()
{
	if(!checkBottom() && !checkCollision(0,1))
		for(int i=0;i<NUM_UNIT;i++)
			moving_squares[i].y++;
}

void onKeyDown(unsigned char keycode)
{
	switch(keycode)
	{
		case KEY_LEFT:
			translate('L');
			break;
		case KEY_RIGHT:
			translate('R');
			break;
		case KEY_UP:
			rotate();
			break;
		case KEY_DOWN:
			drop();
			break;
	}
}

void log()
{
	for(int i=0;i<num_still_squares;i++)
	{
		fprintf(log_file,"i:%d,x:%d,y:%d\n",i,still_squares[i].x,still_squares[i].y);
	}
	fprintf(log_file,"-----------------\n");
	fflush(log_file);
}

void sort(int l,int r)
{
	if(l>=r) return;
	int i=l,j=r;
	Square s = still_squares[l];
	while(i<j)
	{
		while(i<j)
		{
			if(still_squares[j].y < s.y)
			{
				still_squares[i].x = still_squares[j].x;
				still_squares[i].y = still_squares[j].y;
				i++;
				break;
			}
			j--;
		}
		while(i<j)
		{
			if(still_squares[i].y >= s.y)
			{
				still_squares[j].x = still_squares[i].x;
				still_squares[j].y = still_squares[i].y;
				j--;
				break;
			}
			i++;
		}
	}
	still_squares[i].x = s.x;
	still_squares[i].y = s.y;
	sort(l,i);
	sort(i+1,r);
}

void checkElimination()
{
	int y=-1;
	int count=0;
	for(int i=0;i<num_still_squares;i++)
	{
		if(still_squares[i].y == y)
		{
			count++;
		}
		else
		{
			y = still_squares[i].y;
			count = 1;
		}
		if(count == NUM_X)
		{
			for(int j=0;j<i-NUM_X+1;j++)
			{
				still_squares[j].y++;
			}
			memcpy(still_squares+i-NUM_X+1,still_squares+i+1,sizeof(Square)*(num_still_squares - i-1));
			num_still_squares -= NUM_X;
			i -= (NUM_X+1);
		}
	}
}

bool loop()
{
	//check game over
	for(int i=0;i<num_still_squares;i++)
	{
	
		if(still_squares[i].y < 0)
			return false;
	}
	//check bottom and collision
	if(checkBottom() || checkCollision(0,1))
	{
		memcpy(still_squares+num_still_squares,moving_squares,NUM_UNIT*sizeof(Square));
		num_still_squares+=NUM_UNIT;
		
		sort(0,num_still_squares-1);
		checkElimination();
		moving_squares = getNext();
		num_squares = num_still_squares + NUM_UNIT;
	}
	else
	{
		for(int i=0;i<NUM_UNIT;i++)
			moving_squares[i].y++;
	}
	memcpy(squares,still_squares,num_still_squares*sizeof(Square));
	memcpy(squares+num_still_squares,moving_squares,NUM_UNIT*sizeof(Square));
	return true;
}