#include "TetrisData.h"
#include "random.h"

#define NUM_UNIT 4
#define NUM_X 15
#define NUM_Y 23;
#define MAX_SQUARES (NUM_X * NUM_Y)

#define KEY_LEFT 37
#define KEY_RIGHT 38
#define KEY_UP 39
#define KEY_DOWN 40

Square moving_squares[NUM_UNIT];
Square still_squares[];
int num_still_squares;

void initData()
{
	squares = (Square*) calloc(MAX_SQUARES,sizeof(Square));
	num_squares = 0;
	
	still_squares = (Square*) calloc(MAX_SQUARES,sizeof(Square));
	num_still_squares = 0;
}

Square* getNext()
{
	Square* next = (Square*) calloc(NUM_UNIT,sizeof(Square));
	Square start;
	start.x = start.y = 0;
	next[0] = start;
	srand(time(NULL));
	for(int i=1;i<NUM_UNIT;i++)
	{
		int dir = rand_by_range(0,3);
		Square s;
		switch(dir)
		{
			case 0://up
				s.x = start.x;
				s.y = start.y-1;
				break;
			case 1://down
				s.x = start.x;
				s.y = start.y+1;
				break;
			case 2://left
				s.x = start.x-1;
				s.y = start.y;
				break;
			case 3://right
				s.x = start.x+1;
				s.y = start.y;
				break;
		}
		next[i] = s;
		start = s;
	}
	return next;
}

bool checkCollision(Square *moving)
{
	for(int i=0;i<NUM_UNIT;i++)
		moving[i].y++;
	for(int i=0;i<num_still_squares;i++)
	{
		for(int j=0;j<NUM_UNIT;j++)
		{
			if(still_squares[i].x == moving[j].x && still_squares[i].y == moving[j].y)
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
		if(moving_squares[i].x == NUM_X)
			return true;
	}
	return false;
}

bool checkBottom()
{
	for(int i=0;i<NUM_UNIT;i++)
	{
		if(moving_squares[i].y == NUM_Y)
			return true;
	}
	return false;
}

void rotate()
{

}

void translate(char dir)
{
	if(dir == 'L')
	{
		if(!checkLeft()) 
		{
			for(int i=0;i<NUM_UNIT;i++)
				moving[i].x--;
		}
	}
	else if(dir == 'R')
	{
		if(!checkRight()) 
		{
			for(int i=0;i<NUM_UNIT;i++)
				moving[i].x++;
		}
	}
}

void drop()
{
	if(!checkBottom() && !checkCollision(moving_squares))
		for(int i=0;i<NUM_UNIT;i++)
				moving[i].y++;
}

void onKeyDown(const char keycode)
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
			dorp();
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
		memcpy(still_squares,moving_squares,NUM_UNIT*sizeof(Square));
		num_still_squares+=NUM_UNIT;
		moving_squares = getNext();
	}
	else
	{
		for(int i=0;i<NUM_UNIT;i++)
			moving_squares[i].y++;
	}
	return true;
}