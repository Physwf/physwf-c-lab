#include <geom.h>
#include <math.h>

void mirror_transform(vector2d input,vector2d output,vector2d mirror)
{
	float mother = sqrt((mirror[0]) * (mirror[0]) + (mirror[1]) * (mirror[1]));
	float cos_m = mirror[0] / mother;
	float sin_m = mirror[1] / mother;
	matrix2d r1 = {	cos_m,-sin_m, 0,
					sin_m,cos_m	, 0,
					0,		0,    1};
	matrix2d r2 = { 	cos_m,sin_m, 	0,
					-sin_m,cos_m,	0,
					0,		0,    1};
	output[0] = input[0];
	output[1] = input[1];
	matrix2d_transform_vector2d(r1,output);
	output[1] *= -1;
	matrix2d_transform_vector2d(r2,output);
}

