#include "Game.h"
#include "ResourceManager.h"
#include "DWLoadingScene.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::setup()
{
	CCScene* loading = DWLoadingScene::scene();
	CCDirector::sharedDirector()->runWithScene(loading);
	//ResourceManager::instance()->addSpriteFramePack();
}

