#include "HeroPub.h"
#include "Config.h"

HeroPub::HeroPub()
{

}

HeroPub::~HeroPub()
{

}

void HeroPub::initialize()
{
	for (ID i = 1; i < 2;i++)
	{
		mHeros[i] = Config::hero->create(i);
	}
}

Unit* HeroPub::getHero(ID cid)
{
	return mHeros[cid];
}

