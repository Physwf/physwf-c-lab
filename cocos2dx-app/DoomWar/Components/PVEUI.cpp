#include "PVEUI.h"
#include "System.h"


PVEUI::PVEUI()
{
}

PVEUI::~PVEUI()
{

}

PVEUI* PVEUI::create(CCLayer* pve)
{
	PVEUI* pUi = new PVEUI();
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

void PVEUI::onEnter()
{
	TouchGroup::onEnter();
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(mController,1,false);
	getWidgetByName("leftward")->addTouchEventListener(this, toucheventselector(PVEUI::onLeftTouched));
	getWidgetByName("forward")->addTouchEventListener(this, toucheventselector(PVEUI::onForwardTouched));
	getWidgetByName("backward")->addTouchEventListener(this, toucheventselector(PVEUI::onBackwardTouched));
	getWidgetByName("rightward")->addTouchEventListener(this, toucheventselector(PVEUI::onRightwardTouched));
	//System::bag->addEventListener(Bag::BAG_GOLD_CHANGE, this, EventListener(&Scene::onUnitFlop))
}

void PVEUI::onExit()
{
	TouchGroup::onExit();
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(mController);
}

void PVEUI::onLeftTouched(CCObject* object, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		System::pve->step(LEFTWARD);
	}
}

void PVEUI::onForwardTouched(CCObject* object, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		System::pve->step(FORWARD);
	}
}

void PVEUI::onBackwardTouched(CCObject* object, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		System::pve->step(BACKWARD);
	}
}

void PVEUI::onRightwardTouched(CCObject* object, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		System::pve->step(RIGHTWARD);
	}
}

bool PVEUI::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	mPVEBattle->ccTouchBegan(touch,event);
	TouchGroup::ccTouchBegan(touch, event);
	return true;
}


void PVEUI::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	mPVEBattle->ccTouchMoved(touch, event);
	TouchGroup::ccTouchMoved(touch, event);
}

void PVEUI::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	mPVEBattle->ccTouchEnded(touch, event);
	TouchGroup::ccTouchEnded(touch, event);
}

void PVEUI::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
	mPVEBattle->ccTouchCancelled(touch, event);
	TouchGroup::ccTouchCancelled(touch, event);
}

/*PVEUIController*/


PVEUIController::PVEUIController(PVEUI* view)
{
	mView = view;
}

PVEUIController::~PVEUIController()
{

}

PVEUIController* PVEUIController::create(PVEUI* view)
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
