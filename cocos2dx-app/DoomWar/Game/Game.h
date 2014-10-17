#ifndef _GAME_H
#define _GAME_H

#include "DWLoadingScene.h"
#include <cocoa\CCObject.h>
#include "Launcher.h"

class Game : public CCScene
{
public:
	static Game* instance();

	void start();
	void pause();
	void resume();

	void enterWorld();
	void enterPVE(ID mid);
	void enterNoLimit();
private:
	Game();
	~Game();

private:
	
	static Game* mInstance;
	Launcher* mLauncher;

	DWLoadingScene* mLoading;
	PVEMap* mPVE;
};
#endif
