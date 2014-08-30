#include "PVEBattleUI.h"
#include "System.h"

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
	if (pUi && pUi->init())
	{
		pUi->autorelease();
		pUi->addWidget(GUIReader::shareReader()->widgetFromJsonFile("./Data/UIPVE_1/UIPVE_1.ExportJson"));
		//pUi->setAnchorPoint(ccp(-320, -480));
		return pUi;
	}
	return NULL;
}

void PVEBattleUI::onEnter()
{
	TouchGroup::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(mController,0,false);
	getWidgetByName("forward")->addTouchEventListener(this, toucheventselector(PVEBattleUI::onForwardTouched));
}

void PVEBattleUI::onExit()
{
	TouchGroup::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(mController);
}

void PVEBattleUI::onForwardTouched(CCObject* object, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		System::pve->step();
	}
}

/*PVEUIController*/


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
