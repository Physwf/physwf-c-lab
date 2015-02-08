#ifndef _GAME_H
#define _GAME_H

#include "DWLoading.h"
#include <cocoa/CCObject.h>
#include "Launcher.h"

#define GAME_WIDTH 640
#define GAME_HEIGHT 960

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
