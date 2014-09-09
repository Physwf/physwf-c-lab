#include "PVEBattleUI.h"
#include "System.h"


PVEBattleUI::PVEBattleUI()
{
}

PVEBattleUI::~PVEBattleUI()
{

}

PVEBattleUI* PVEBattleUI::create(CCLayer* pve)
{
	PVEBattleUI* pUi = new PVEBattleUI();
	if (pUi && pUi->init())
	{
		pUi->autorelease();
		pUi->addWidget(GUIReader::shareReader()->widgetFromJsonFile("./Data/UIPVE_1/UIPVE_1.ExportJson"));
		pUi->mPVEBattle = pve;
		//pUi->setAnchorPoint(ccp(-320, -480));
		return pUi;
	}
	return NULL;
}

void PVEBattleUI::onEnter()
{
	TouchGroup::onEnter();
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(mController,1,false);
	getWidgetByName("leftward")->addTouchEventListener(this, toucheventselector(PVEBattleUI::onLeftTouched));
	getWidgetByName("forward")->addTouchEventListener(this, toucheventselector(PVEBattleUI::onForwardTouched));
	getWidgetByName("backward")->addTouchEventListener(this, toucheventselector(PVEBattleUI::onBackwardTouched));
	getWidgetByName("rightward")->addTouchEventListener(this, toucheventselector(PVEBattleUI::onRightwardTouched));
}

void PVEBattleUI::onExit()
{
	TouchGroup::onExit();
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(mController);
}

void PVEBattleUI::onLeftTouched(CCObject* object, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		System::pve->step(LEFTWARD);
	}
}

void PVEBattleUI::onForwardTouched(CCObject* object, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		System::pve->step(FORWARD);
	}
}

void PVEBattleUI::onBackwardTouched(CCObject* object, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		System::pve->step(BACKWARD);
	}
}

void PVEBattleUI::onRightwardTouched(CCObject* object, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		System::pve->step(RIGHTWARD);
	}
}

bool PVEBattleUI::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	mPVEBattle->ccTouchBegan(touch,event);
	return TouchGroup::ccTouchBegan(touch, event);
}


void PVEBattleUI::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	mPVEBattle->ccTouchMoved(touch, event);
}

void PVEBattleUI::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	mPVEBattle->ccTouchEnded(touch, event);
}

void PVEBattleUI::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
	mPVEBattle->ccTouchCancelled(touch, event);
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
