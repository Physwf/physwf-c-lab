#include "Launcher.h"
#include "ResourceManager.h"
#include "Game.h"

EType const Launcher::SET_UP_SUCCESS = "set_up_success";

Launcher::Launcher()
{

}

Launcher::~Launcher()
{

}

void Launcher::setup()
{
	ResourceManager::instance()->loadTexture("./Data/units.png", this, callfuncO_selector(Launcher::onUnitSpriteComplete));
}

void Launcher::onUnitSpriteComplete(CCObject* tex)
{
	CCTexture2D* texUnits = (CCTexture2D*)tex;
	ResourceManager::instance()->addSpriteFramePack("./Data/units.plist", texUnits);
	ResourceManager::instance()->loadTexture("./Data/skills.png", this, callfuncO_selector(Launcher::onSkillSpriteComplete));
}

void Launcher::onSkillSpriteComplete(CCObject* tex)
{
	CCTexture2D* skills = (CCTexture2D*)tex;
	ResourceManager::instance()->addSpriteFramePack("./Data/skills.plist", skills);
	//ice
	CCArray *frames = CCArray::create();
	for (int i = 1; i < 28; i++)
	{
		CCString* name = CCString::createWithFormat("ice%04d", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "ice");
	//axe
	frames->removeAllObjects();
	for (int i = 2; i < 19; i++)
	{
		CCString* name = CCString::createWithFormat("fuzi%04d", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "axe");
	//heal
	frames->removeAllObjects();
	for (int i = 1; i < 46; i++)
	{
		CCString* name = CCString::createWithFormat("heal%04d", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "heal");
	//dagger
	frames->removeAllObjects();
	for (int i = 1; i < 7; i++)
	{
		CCString* name = CCString::createWithFormat("dagger%04d", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "dagger");
	//arrow
	frames->removeAllObjects();
	for (int i = 1; i < 7; i++)
	{
		CCString* name = CCString::createWithFormat("arrow%04d", i);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(name->getCString());
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "arrow");
	//fireball
	frames->removeAllObjects();
	for (int i = 1; i < 7; i++)
	{
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame("fireball");
		frames->addObject(frame);
	}
	ResourceManager::instance()->addAnimation(CCAnimation::createWithSpriteFrames(frames, 0.02f), "fireball");

	ResourceManager::instance()->loadXML("./Data/heros.xml", Config::hero, (Config::OnConfigLoaded)&HeroConfig::onHeroConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/monsters.xml", Config::monster, (Config::OnConfigLoaded)&MonsterConfig::onMonsterConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/barriers.xml", Config::barrier, (Config::OnConfigLoaded)&BarrierConfig::onBarrierConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/gset.xml", Config::skill, (Config::OnConfigLoaded)&SkillConfig::onGSetConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/skills.xml", Config::skill, (Config::OnConfigLoaded)&SkillConfig::onSkillConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/buffs.xml", Config::skill, (Config::OnConfigLoaded)&SkillConfig::onBuffConfigLoaded);
	ResourceManager::instance()->loadXML("./Data/items.xml", Config::item, (Config::OnConfigLoaded)&ItemConfig::onItemConfigLoaded);

	ResourceManager::instance()->loadTexture("./Data/ui.png", this, callfuncO_selector(Launcher::onUISpriteComplete));
	
}

void Launcher::onUISpriteComplete(CCObject* tex)
{
	CCTexture2D* texUnits = (CCTexture2D*)tex;
	ResourceManager::instance()->addSpriteFramePack("./Data/ui.plist", texUnits);
	onMapSpriteComplete(NULL);
}

void Launcher::onMapSpriteComplete(CCObject* tex)
{
	onAllComplete();
}

void Launcher::onAllComplete()
{
	Game::instance()->initWorld();
}