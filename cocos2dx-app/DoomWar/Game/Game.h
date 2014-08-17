#ifndef _GAME_H
#define _GAME_H

#include "DWLoadingScene.h"
#include <cocoa\CCObject.h>

class Game : public CCObject
{
public:
	static Game* instance();

	void pause();
	void resume();

	void setup();
	
private:
	Game();
	~Game();

	void onUnitSpriteComplete(CCObject* tex);
	void onMapSpriteComplete(CCObject* tex);
	void onAllComplete();

private:
	DWLoadingScene* mLoading;

	static Game* mInstance;
};
#endif
