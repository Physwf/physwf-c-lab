#include <color_matrix.h>
#include <string.h>
#include <math.h>

#define LUMA_R 0.299
#define LUMA_G 0.587
#define LUMA_B 0.114

void adjustHue(color_matrix mat,float value)
{
	float cos_v = cos(value);
	float sin_v = sin(value);
	color_matrix temp1;
	memcpy(temp1,mat,sizeof(mat));
	color_matrix temp2 = 
	{
		 ((LUMA_R + (cos_v * (1 - LUMA_R))) + (sin_v * -(LUMA_R))), ((LUMA_G + (cos_v * -(LUMA_G))) + (sin_v * -(LUMA_G))), ((LUMA_B + (cos_v * -(LUMA_B))) + (sin_v * (1 - LUMA_B))), 0, 0,
		((LUMA_R + (cos_v * -(LUMA_R))) + (sin_v * 0.143)), ((LUMA_G + (cos_v * (1 - LUMA_G))) + (sin_v * 0.14)), ((LUMA_B + (cos_v * -(LUMA_B))) + (sin_v * -0.283)), 0, 0,
		((LUMA_R + (cos_v * -(LUMA_R))) + (sin_v * -((1 - LUMA_R)))), ((LUMA_G + (cos_v * -(LUMA_G))) + (sin_v * LUMA_G)), ((LUMA_B + (cos_v * (1 - LUMA_B))) + (sin_v * LUMA_B)), 0, 0,
		0, 0, 0, 1, 0
	};
	concat(temp2,mat,temp1);
	memcpy(mat,temp1,sizeof(temp1));
}

void adjustSaturation(color_matrix mat,float sat)
{
	sat += 1;    
	float invSat  = 1 - sat;
	float invLumR = invSat * LUMA_R;
	float invLumG = invSat * LUMA_G;
	float invLumB = invSat * LUMA_B;
	color_matrix temp1;
	memcpy(temp1,mat,sizeof(mat));
	color_matrix temp2 = 
	{
		(invLumR + sat), invLumG, invLumB, 0, 0,
		 invLumR, (invLumG + sat), invLumB, 0, 0,
		 invLumR, invLumG, (invLumB + sat), 0, 0,
		 0, 0, 0, 1, 0
	};
	concat(temp2,mat,temp1);
	memcpy(mat,temp1,sizeof(temp1));
}

void adjustBrightness(color_matrix mat,float value)
{
	 value *= 255;
	 color_matrix temp1;
	memcpy(temp1,mat,sizeof(mat));
	color_matrix temp2 = 
	{
		1, 0, 0, 0, value,
		0, 1, 0, 0, value,
		0, 0, 1, 0, value,
		0, 0, 0, 1, 0
	};
	concat(temp2,mat,temp1);
	memcpy(mat,temp1,sizeof(temp1));
}

void adjustContrast(color_matrix mat,float value)
{
	float s = value + 1;
	float o = 128 * (1 - s);
	color_matrix temp1;
	memcpy(temp1,mat,sizeof(mat));
	color_matrix temp2 = 
	{
		s, 0, 0, 0, o,
		0, s, 0, 0, o,
		0, 0, s, 0, o,
		0, 0, 0, 1, 0
	};
	concat(temp2,mat,temp1);
	memcpy(mat,temp1,sizeof(temp1));
}

void invert(color_matrix mat)
{
	color_matrix temp1;
	memcpy(temp1,mat,sizeof(mat));
	color_matrix temp2 = 
	{
		-1,  0,  0,  0, 255,
		0, -1,  0,  0, 255,
		0,  0, -1,  0, 255,
		0,  0,  0,  1,   0
	};
	concat(temp2,mat,temp1);
	memcpy(mat,temp1,sizeof(temp1));
}

void concat(color_matrix left,color_matrix right,color_matrix out)
{
	int i = 0;

	for (int y=0; y<4; ++y)
	{
		for (int x=0; x<5; ++x)
		{
			out[(i+x)] = 
				left[i]    	* right[x]        +
				left[(i+1)] * right[(x +  5)] +
				left[(i+2)] * right[(x + 10)] +
				left[(i+3)] * right[(x + 15)] +
				(x == 4 ? left[(i+4)] : 0);
		};
		i+=5;
	};
}