#ifndef _GAME_H
#define _GAME_H

#include "DWLoadingScene.h"
#include <cocoa\CCObject.h>
#include "Launcher.h"

class Game : public CCScene, public DWObject
{
public:
	static Game* instance();

	void start();
	void pause();
	void resume();

private:
	Game();
	~Game();
	void onLaunchSuccess(Event* e);

private:
	DWLoadingScene* mLoading;

	static Game* mInstance;
	Launcher* mLauncher;
};
#endif
