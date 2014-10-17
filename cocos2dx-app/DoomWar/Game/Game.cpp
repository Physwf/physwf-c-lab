#include "Game.h"
#include "ResourceManager.h"
#include "System.h"
#include "Engine.h"


Game::Game()
{

}

Game::~Game()
{

}

Game* Game::mInstance = NULL;

Game* Game::instance()
{
	if (mInstance == NULL)
		mInstance = new Game();
	return mInstance;
}

void Game::pause()
{
	CCDirector::sharedDirector()->stopAnimation();
}

void Game::resume()
{
	CCDirector::sharedDirector()->startAnimation();
}

void Game::start()
{
	mLoading = DWLoadingScene::create();
	CCDirector::sharedDirector()->runWithScene(mLoading->scene());
	mLauncher = new Launcher();
	mLauncher->setup();
	delete mLauncher;
}

void Game::enterWorld()
{

}

void Game::enterPVE(ID mid)
{
	System::pub->initialize();
	Engine::scene->initialize();
	//temp 
	Unit* heros[5];
	heros[0] = System::pub->getHero(1001);
	heros[1] = System::pub->getHero(1002);
	heros[2] = System::pub->getHero(1003);
	heros[3] = System::pub->getHero(1004);
	heros[4] = System::pub->getHero(1005);

	Engine::scene->enterPVEMap(mid, heros, 5);
}

void Game::enterNoLimit()
{

}
