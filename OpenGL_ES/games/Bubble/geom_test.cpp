#include <stdio.h>
#include <geom.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(int argc,char** argv)
{
	vector2d v;
	vector2d_print(v);
	v[0] = 1;
	vector2d_print(v);
	vector2d_rotate(v,M_PI/2);
	vector2d_print(v);
	getchar();
	return 0;
}
