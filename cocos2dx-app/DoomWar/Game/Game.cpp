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
	ResourceManager::instance()->loadTexture("./Data/units.png", this, callfuncO_selector(Game::onUnitSpriteComplete));
}

void Game::onUnitSpriteComplete(CCObject* tex)
{
	CCTexture2D* texUnits = (CCTexture2D*)tex;
	ResourceManager::instance()->addSpriteFramePack("./Data/units.plist", texUnits);
	ResourceManager::instance()->loadTexture("./Data/skills.png", this, callfuncO_selector(Game::onSkillSprite));
}

void Game::onSkillSprite(CCObject* tex)
{
	CCTexture2D* skills = (CCTexture2D*)tex;
	ResourceManager::instance()->addSpriteFramePack("./Data/skills.plist", skills);
	//ice
	CCArray *frames = CCArray::create();
	for (int i = 1; i < 28; i++)
	{
		CCString* name = CCString::createWithFormat("ice%04d.png", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "ice");
	//axe
	frames->removeAllObjects();
	for (int i = 2; i < 19; i++)
	{
		CCString* name = CCString::createWithFormat("fuzi%04d.png", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "axe");
	//heal
	frames->removeAllObjects();
	for (int i = 1; i < 46; i++)
	{
		CCString* name = CCString::createWithFormat("heal%04d.png", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "heal");
	//dagger
	frames->removeAllObjects();
	for (int i = 1; i < 7; i++)
	{
		CCString* name = CCString::createWithFormat("dagger%04d.png", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "dagger");
	//arrow
	frames->removeAllObjects();
	for (int i = 1; i < 7; i++)
	{
		CCString* name = CCString::createWithFormat("arrow%04d.png", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "arrow");

	ResourceManager::instance()->loadXML("./Data/heros.xml", Config::hero, (Config::OnConfigLoaded)&HeroConfig::onHeroConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/monsters.xml", Config::monster, (Config::OnConfigLoaded)&MonsterConfig::onMonsterConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/barriers.xml", Config::barrier, (Config::OnConfigLoaded)&BarrierConfig::onBarrierConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/skills.xml", Config::skill, (Config::OnConfigLoaded)&SkillConfig::onSkillConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/buffs.xml", Config::skill, (Config::OnConfigLoaded)&SkillConfig::onBuffConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/items.xml", Config::item, (Config::OnConfigLoaded)&ItemConfig::onItemConfigLoaded);

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
	Unit* heros[5];
	heros[0] = System::pub->getHero(1001);
	heros[1] = System::pub->getHero(1002);
	heros[2] = System::pub->getHero(1003);
	heros[3] = System::pub->getHero(1004);
	heros[4] = System::pub->getHero(1005);

	Engine::scene->enterPVEMap(0, heros, 5);
}