#ifndef _CONFIG_H
#define _CONFIG_H

#include "Unit.h"
#include "dwtype.h"

class HeroConfig
{
public:
	Unit* create(ID cid);
private:

};

class BarrierConfig
{
public:
	Unit* create(ID cid);
private:
};

class MonsterConfig
{
public:
	Unit* create(ID cid);
};
class Config
{
public:
	static HeroConfig* hero;
	static BarrierConfig* barrier;
	static MonsterConfig* monster;
};


#endif