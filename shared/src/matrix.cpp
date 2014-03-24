#include <geom/matrix.h>
#include <math.h>
#include <stdio.h>
/*
	0,1,2,   a ,c , tx,
	3,4,5,	 b ,d , ty,
	6,7,8	 u,	v , w
*/
void matrix2d_concat(matrix2d source,matrix2d m)
{
	float a = source[0] * m[0] + source[1] * m[3] + source[2] * m[6];
	float c = source[0] * m[1] + source[1] * m[4] + source[2] * m[7];
	float tx = source[0] * m[2] + source[1] * m[5] + source[2] * m[8];
	float b = source[3] * m[0] + source[4] * m[3] + source[5] * m[6];
	float d = source[3] * m[1] + source[4] * m[4] + source[5] * m[7];
	float ty = source[3] * m[2] + source[4] * m[5] + source[5] * m[8];
	float u = source[6] * m[0] + source[7] * m[3] + source[8] * m[6];
	float v = source[6] * m[1] + source[7] * m[4] + source[8] * m[7];
	float w = source[6] * m[2] + source[7] * m[5] + source[8] * m[8];
	
	 source[0] = a; source[1] = c; source[2] = tx; 
	 source[3] = b; source[4] = d; source[5] = ty; 
	 source[6] = u; source[7] = v; source[8] = w; 
}

void matrix2d_rotate(matrix2d source,float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	matrix2d r = { 	c, -s, 0.0,
					s, c,  0.0,
					0.0, 0.0,  1.0  };
	matrix2d_concat(source,r);
}

void matrix2d_transform_vector2d(matrix2d source,vector2d v)
{
	float x = source[0]*v[0] + source[1]*v[1];
	float y = source[3]*v[0] + source[4]*v[1];
	v[0] = x; v[1] = y;
}

void matrix2d_get_identity(matrix2d output)
{
	output[0] = output[4] = output[8] = 1;
	output[1] = output[2] = output[3] = output[5] = output[6] = output[7] = 0;
}

void matrix2d_print(matrix2d source)
{
	printf("a:%f,c:%f,tx:%f,\n",source[0],source[1],source[2]);
	printf("b:%f,d:%f,ty:%f,\n",source[3],source[4],source[5]);
	printf("u:%f,v:%f,w:%f\n",source[6],source[7],source[8]);
}