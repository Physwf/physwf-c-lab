#include <stdio.h>
#include <string.h>

typedef struct square{
	int x;
	int y;
} Square;

Square squares[];
Square num_sqares;

void initData();
void onKeyDown(const char keycode);
bool loop();
