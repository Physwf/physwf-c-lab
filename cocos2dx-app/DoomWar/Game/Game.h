#ifndef _GAME_H
#define _GAME_H

#include "PVEBattleScene.h"

class Game
{
public:
	Game();
	~Game();

	void setup();
	//void enterPVEBattle();


private:
	PVEBattleScene* mPVEScene;
};
#endif
