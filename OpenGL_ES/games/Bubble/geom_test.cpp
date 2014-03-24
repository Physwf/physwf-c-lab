#include <stdio.h>
#include <geom/affine.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(int argc,char** argv)
{
	vector2d v = {1,0};
	//vector2d_rotate(v,M_PI/3);
	vector2d_print(v);
	vector2d mirror = {0,-1};
	vector2d output;
	affine_mirror_transform(v,output,mirror);
	vector2d_print(output);
	getchar();
	return 0;
}
