#include <assert.h>
#include "random.h"

int rand_by_range(int min,int max)
{
	assert(min<max);
	return rand() % (max - min);
}

float random()
{
	return (float) rand() / RAND_MAX;
}