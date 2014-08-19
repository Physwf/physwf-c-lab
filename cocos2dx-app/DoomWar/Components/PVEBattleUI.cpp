#include "PVEBattleUI.h"

PVEBattleUI::PVEBattleUI()
{
	mController = new PVEUIController(this);
}

PVEBattleUI::~PVEBattleUI()
{

}

PVEBattleUI* PVEBattleUI::create()
{
	PVEBattleUI* pUi = new PVEBattleUI();
	if (pUi && pUi->initWithFile("./Data/UIPVEBattle.png"))
	{
		pUi->autorelease();
		pUi->setAnchorPoint(ccp(0, 0));
		return pUi;
	}
	return NULL;
}

void PVEBattleUI::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(mController,0,false);
	CCSprite::onEnter();
}

void PVEBattleUI::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(mController);
	CCSprite::onExit();
}

/*PVEUIController*/
#include "System.h"

PVEUIController::PVEUIController(PVEBattleUI* view)
{
	mView = view;
}

PVEUIController::~PVEUIController()
{

}

PVEUIController* PVEUIController::create(PVEBattleUI* view)
{
	PVEUIController* controller = new PVEUIController(view);
	return NULL;
}

bool PVEUIController::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	System::pve->step();
	return true;
}

void PVEUIController::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

}

void PVEUIController::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

}

void PVEUIController::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{

}
