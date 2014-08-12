#ifndef _GAME_H
#define _GAME_H

#include "PVEBattleScene.h"
#include <cocoa\CCObject.h>

class Game : public CCObject
{
public:
	static Game* instance();

	void pause();
	void resume();

	void setup();
	
	//void enterPVEBattle();

private:
	Game();
	~Game();

	void onUnitSpriteComplete(CCObject* tex);
	void onMapSpriteComplete(CCObject* tex);
	void onAllComplete();

private:
	CCScene* mLoading;
	CCScene* mPVEScene;

	static Game* mInstance;
};
#endif
