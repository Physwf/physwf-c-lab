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

void Game::setup()
{
	mLoading = DWLoadingScene::create();
	CCDirector::sharedDirector()->runWithScene(mLoading->scene());
	ResourceManager::instance()->load("./Data/units.png", this, callfuncO_selector(Game::onUnitSpriteComplete));
}

void Game::onUnitSpriteComplete(CCObject* tex)
{
	CCTexture2D* texUnits = (CCTexture2D*)tex;
	ResourceManager::instance()->addSpriteFramePack("./Data/units.plist", texUnits);
	ResourceManager::instance()->load("./Data/ice.png", this, callfuncO_selector(Game::onSkillSprite));
}

void Game::onSkillSprite(CCObject* tex)
{
	CCTexture2D* axeUnits = (CCTexture2D*)tex;
	ResourceManager::instance()->addSpriteFramePack("./Data/ice.plist", axeUnits);
	CCArray *axeFrames = CCArray::create();
	for (int i = 1; i < 28; i++)
	{
		CCString* name = CCString::createWithFormat("ice%04d.png", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		axeFrames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(axeFrames),"ice");
	onMapSpriteComplete(NULL);
}

void Game::onMapSpriteComplete(CCObject* tex)
{
	onAllComplete();
}

void Game::onAllComplete()
{
	System::pub->initialize();
	Engine::scene->initialize();
	//temp 
	
	Unit* hero = System::pub->getHero(1);
	
	Engine::scene->enterPVEMap(0, hero, 1);
}