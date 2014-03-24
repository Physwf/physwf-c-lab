#include <physics/kinematics.h>
#define _USE_MATH_DEFINES
#include <math.h>

void particle_eslatic_collide(particle_p a,particle_p b,float factor)
{
	vector2d offset = { b->px - a->px , b->py - a->py};
	vector2d_rotate(offset,M_PI/2);
	vector2d mom_a = { a->m*a->vx,a->m*a->vy };
	vector2d mom_b = { b->m*b->vx,b->m*b->vy };
	affine_mirror_transform(mom_a,mom_a,offset);
	affine_mirror_transform(mom_b,mom_b,offset);
	
}