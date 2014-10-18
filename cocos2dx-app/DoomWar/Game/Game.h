#ifndef _GAME_H
#define _GAME_H

#include "DWLoadingScene.h"
#include <cocoa\CCObject.h>
#include "Launcher.h"

class Game
{
public:
	static Game* instance();

	void start();
	void pause();
	void resume();

	void initWorld();

	void replaceView(CCLayer* view);
private:
	Game();
	~Game();

private:
	
	static Game* mInstance;
	Launcher* mLauncher;

	CCScene* mScene;
	CCLayer* mCurrentView;
	DWLoading* mLoading;
};
#endif
