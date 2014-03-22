#include <geom.h>

void mirror_transform(vector2* input,vector2* output,vector2* mirror)
{
	float mother = (*mirror[0]) * (*mirror[0]) + (*mirror[1]) * (*mirror[1]);
	float cos_m = *mirror[0] / mother;
	float sin_m = *mirror[1] / mother;
	matrix2 r = {cos_m,-sin_m,cos_m,sin_m};
}