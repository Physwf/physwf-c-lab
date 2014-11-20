#include <physics/kinematics.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

void particle_eslatic_collide(particle_p a,particle_p b)
{
	vector2d offset = { b->px - a->px , b->py - a->py};
	vector2d_rotate(offset,M_PI/2);
	vector2d u_a = { a->vx,a->vy };
	vector2d u_b = { b->vx,b->vy };
	float m_a = a->m;
	float m_b = b->m;
	affine_mirror_transform(u_a,u_a,offset);
	affine_mirror_transform(u_b,u_b,offset);
	float u_a_y = u_a[1];
	float u_b_y = u_b[1];
	printf("u_a_y:%f,u_b_y:%f\n",u_a_y,u_b_y);
	//see http://en.wikipedia.org/wiki/Elastic_collision
	float v_a_y = (u_a_y * (m_a - m_b) + 2 * m_b * u_b_y) / (m_a + m_b);
	float v_b_y = (u_b_y * (m_b - m_a) + 2 * m_a * u_a_y) / (m_a + m_b);
	printf("v_a_y:%f,v_b_y:%f\n",v_a_y,v_b_y);
	u_a[1] = v_a_y;
	u_b[1] = v_b_y;
	a->vx = u_a[0]; a->vy = u_a[1];
	b->vx = u_b[0]; b->vy = u_b[1];
}