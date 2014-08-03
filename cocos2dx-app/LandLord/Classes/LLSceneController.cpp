#include "LLSceneController.h"
#include "game.h"
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

LLSceneController::LLSceneController()
{

};

LLSceneController::~LLSceneController()
{

};

void LLSceneController::showWaitForMorePlayers()
{
	CCTexture2D *tStart = new CCTexture2D();
	CCSize size(92,36);
	tStart->initWithString("Start", "Arial", 15, size, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	
	CCSpriteFrame * fButton = new CCSpriteFrame();
	CCRect rect(0, 0, size.width,size.height);
	fButton->initWithTexture(tStart, rect);

	CCScale9Sprite
};

void LLSceneController::showPlayerJoin()
{

};

void LLSceneController::showDealResult()
{
	
};

void LLSceneController::showLootScore()
{

};

void LLSceneController::showLootResult()
{

};


void LLSceneController::showPlayCards()
{

};

void LLSceneController::showGameOver()
{

};