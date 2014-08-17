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

class Config
{
public:
	static HeroConfig* hero;
};
#endif