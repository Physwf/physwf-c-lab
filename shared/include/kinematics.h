#include <geom.h>

typedef struct particle_t
{
	float m;
	float vx;
	float vy;
} *particle_p;

void particle_eslatic_collide(particle_p a,particle_p b);