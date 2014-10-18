#include "Game.h"
#include "ResourceManager.h"
#include "System.h"
#include "Engine.h"


Game::Game() :mCurrentView(NULL)
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
	mLoading = DWLoading::create();
	mScene = CCScene::create();
	CCDirector::sharedDirector()->runWithScene(mScene);
	replaceView(mLoading);

	
	mLauncher = new Launcher();
	mLauncher->setup();
	delete mLauncher;
}

void Game::initWorld()
{
	System::pub->initialize();
	Engine::world->initialize();
	//temp 
	Unit* heros[5];
	heros[0] = System::pub->getHero(1001);
	heros[1] = System::pub->getHero(1002);
	heros[2] = System::pub->getHero(1003);
	heros[3] = System::pub->getHero(1004);
	heros[4] = System::pub->getHero(1005);

	Engine::world->enterPVEView(0, heros, 5);
}

void Game::replaceView(CCLayer* view)
{
	if (mCurrentView != NULL)
	{
		mScene->removeChild(mCurrentView);
	}
	mCurrentView = view;
	mScene->addChild(mCurrentView);
}