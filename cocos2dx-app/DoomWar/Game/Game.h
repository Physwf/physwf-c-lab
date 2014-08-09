#ifndef _GAME_H
#define _GAME_H

#include "PVEBattleScene.h"

class Game
{
public:
	Game();
	~Game();

	void init();

private:
	PVEBattleScene* mPVEScene;
};
#endif
