#ifndef _ENGINE_H
#define _ENGINE_H

#include "World.h"

class Engine
{
private:
	Engine();
	~Engine();
public:
	static World* world;
};
#endif