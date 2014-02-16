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

Square* getNext()
{
	Square* next = (Square*) calloc(NUM_UNIT,sizeof(Square));
	Square* start = next;
	start->x = NUM_X / 2;
	start->y = 0;
	srand(time(NULL));
	int dirs[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
	int dir[2] = {0,0};
	for(int i=1;i<NUM_UNIT;i++)
	{
		int j = rand_by_range(0,3);
		while(dirs[j][0] * dir[0] + dirs[j][1] * dir[1] == -1)
		{
			j = rand_by_range(0,3);
		}
		memcpy(dir,dirs[j],sizeof(dir));
		Square* s = next+i;
		s->x = start->x + dir[0];
		s->y = start->y + dir[1];
		start = s;
	}
	return next;
}

void initData()
{
	squares = (Square*) calloc(MAX_SQUARES,sizeof(Square));
	
	
	still_squares = (Square*) calloc(MAX_SQUARES,sizeof(Square));
	num_still_squares = 0;
	
	moving_squares = getNext();
	num_squares = NUM_UNIT;
}

bool checkCollision(Square *moving)
{
	for(int i=0;i<num_still_squares;i++)
	{
		for(int j=0;j<NUM_UNIT;j++)
		{
			if(still_squares[i].x == moving[j].x && still_squares[i].y == moving[j].y+1)
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
		printf("%dx:%d\n",i,moving_squares[i].x);
		printf("%dy:%d\n",i,moving_squares[i].y);
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
	printf("center_x:%d\n",center_x);
	printf("center_y:%d\n",center_y);
	printf("org_x:%d\n",org_x);
	printf("org_y:%d\n",org_y);
	/* rotate matrix
	|0  1|
	|-1 0|
	*/
	for(int i=0;i<NUM_UNIT;i++)
	{
		int x = (moving_squares[i].y - center_y - org_y) * (1);
		int y = (moving_squares[i].x - center_x - org_x) * (-1);
		moving_squares[i].x = x + org_x + center_x;
		moving_squares[i].y = y + org_y + center_y;
		printf("%dx:%d\n",i,moving_squares[i].x);
		printf("%dy:%d\n",i,moving_squares[i].y);
	}
	
}

void translate(char dir)
{
	printf("translate:%c\n",dir);
	if(dir == 'L')
	{
		if(!checkLeft()) 
		{
			for(int i=0;i<NUM_UNIT;i++)
				moving_squares[i].x--;
		}
	}
	else if(dir == 'R')
	{
		if(!checkRight()) 
		{
			for(int i=0;i<NUM_UNIT;i++)
				moving_squares[i].x++;
		}
	}
}

void drop()
{
	if(!checkBottom() && !checkCollision(moving_squares))
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

bool loop()
{
	//check game over
	for(int i=0;i<num_still_squares;i++)
	{
	
		if(still_squares[i].y < 0)
			return false;
	}
	//check bottom and collision
	if(checkBottom() || checkCollision(moving_squares))
	{
		memcpy(still_squares+num_still_squares,moving_squares,NUM_UNIT*sizeof(Square));
		num_still_squares+=NUM_UNIT;
		moving_squares = getNext();
		num_squares = num_still_squares + NUM_UNIT;
	}
	else
	{
		for(int i=0;i<NUM_UNIT;i++)
			moving_squares[i].y++;
	}
	memcpy(squares,still_squares,NUM_UNIT*sizeof(Square));
	memcpy(squares+num_still_squares,moving_squares,NUM_UNIT*sizeof(Square));
	printf("num_still_squares:%d\n",num_still_squares);
	for(int i=0;i<num_still_squares;i++)
	{
		// printf("%dx:%d\n",i,still_squares[i].x);
		// printf("%dy:%d\n",i,still_squares[i].y);
	}
	for(int i=0;i<NUM_UNIT;i++)
	{
		// printf("%dx:%d\n",i,moving_squares[i].x);
		// printf("%dy:%d\n",i,moving_squares[i].y);
	}
	return true;
}