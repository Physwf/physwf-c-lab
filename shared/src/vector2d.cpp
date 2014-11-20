#include <geom/matrix.h>
#include <stdio.h>
#include <math.h>

void vector2d_rotate(vector2d source,float angle)
{
	matrix2d mr={0};
	matrix2d_get_identity(mr);
	matrix2d_rotate(mr,angle);
	float x = mr[0]*(source[0])+mr[1]*(source[1]);
	float y = mr[3]*(source[0])+mr[4]*(source[1]);
	source[0] = x;
	source[1] = y;
}

float vector2d_get_angle_between(vector2d v1,vector2d v2)
{
	float dot_prod = v1[0]*v2[0] + v1[1]*v2[1];
	float model_1 = sqrt(v1[0]*v1[0]+v1[1]*v1[1]);
	float model_2 = sqrt(v2[0]*v2[0]+v2[1]*v2[1]);
	float cos_theta = dot_prod / (model_1 * model_2);
	return acosf(cos_theta);
	return 0;
}

void vector2d_print(vector2d source)
{
	printf("x:%f,y:%f\n",source[0],source[1]);
}