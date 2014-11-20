#include <stdio.h>
#include <geom/affine.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <physics/kinematics.h>

int main(int argc,char** argv)
{
	vector2d v = {1,0};
	//vector2d_rotate(v,M_PI/3);
	vector2d_print(v);
	vector2d mirror = {0,-1};
	vector2d output;
	affine_mirror_transform(v,output,mirror);
	vector2d_print(output);
	particle_t a = {1,10,20,23,24};
	particle_t b = {1,30,50,33,14};
	particle_eslatic_collide(&a,&b);
	printf("a m:%f,px:%f,py:%f,vx:%f,vy:%f\n",a.m,a.px,a.py,a.vx,a.vy);
	printf("b m:%f,px:%f,py:%f,vx:%f,vy:%f\n",b.m,b.px,b.py,b.vx,b.vy);
	getchar();
	return 0;
}
