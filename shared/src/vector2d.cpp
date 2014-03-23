#include <matrix.h>
#include <stdio.h>

void vector2d_rotate(vector2d source,float angle)
{
	matrix2d mr={0};
	matrix2d_print(mr);
	matrix2d_get_identity(mr);
	matrix2d_rotate(mr,angle);
	matrix2d_print(mr);
	float x = mr[0]*(source[0])+mr[1]*(source[1]);
	float y = mr[3]*(source[0])+mr[4]*(source[1]);
	source[0] = x;
	source[1] = y;
}

float get_angle_between(vector2d v1,vector2d v2)
{
	return 0;
}

void vector2d_print(vector2d source)
{
	printf("x:%f,y:%f\n",source[0],source[1]);
}