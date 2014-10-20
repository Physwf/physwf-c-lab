#include "PVEUI.h"
#include "System.h"


PVEUI::PVEUI()
{
}

PVEUI::~PVEUI()
{

}

bool PVEUI::init()
{
	mMask = CCSprite::create();

	CCSprite* maskL = CCSprite::createWithSpriteFrameName("left-mask");
	maskL->setScaleY(960);
	maskL->setAnchorPoint(CCPoint(0,0));
	maskL->setPosition(CCPoint(0, 0));
	mMask->addChild(maskL);

	CCSprite* maskUp = CCSprite::createWithSpriteFrameName("up-mask");
	maskUp->setScaleX(640);
	maskUp->setAnchorPoint(CCPoint(0, 1));
	maskUp->setPosition(CCPoint(0,960));
	mMask->addChild(maskUp);

	CCSprite* maskR = CCSprite::createWithSpriteFrameName("right-mask");
	maskR->setScaleY(960);
	maskR->setAnchorPoint(CCPoint(1, 0));
	maskR->setPosition(CCPoint(640, 0));
	mMask->addChild(maskR);

	CCSprite* maskD = CCSprite::createWithSpriteFrameName("down-mask");
	maskD->setScaleX(640);
	maskD->setAnchorPoint(CCPoint(0, 0));
	mMask->addChild(maskD);

	addChild(mMask);

	mDashBoard = UILayout::create();

	UIImageView* frame = UIImageView::create();
	frame->loadTexture("frame",UI_TEX_TYPE_PLIST);
	frame->setAnchorPoint(CCPoint(0, 0));
	mDashBoard->addChild(frame);

	mBtnLeft = UIButton::create();
	mBtnLeft->loadTextures("left-button", "left-button", "left-button",UI_TEX_TYPE_PLIST);
	mDashBoard->addChild(mBtnLeft);

	mBtnForward = UIButton::create();
	mBtnForward->loadTextures("forward-button", "forward-button", "forward-button", UI_TEX_TYPE_PLIST);
	mDashBoard->addChild(mBtnForward);

	mBtnBackward = UIButton::create();
	mBtnBackward->loadTextures("backward-button", "backward-button", "backward-button", UI_TEX_TYPE_PLIST);
	mDashBoard->addChild(mBtnBackward);

	mBtnRight = UIButton::create();
	mBtnRight->loadTextures("right-button", "right-button", "right-button", UI_TEX_TYPE_PLIST);
	mDashBoard->addChild(mBtnRight);

	addChild(mDashBoard);
	//UIButton
	return true;
}

PVEUI* PVEUI::create(CCLayer* pve)
{
	PVEUI* pUi = new PVEUI();
	if (pUi && pUi->init())
	{
		pUi->autorelease();
		//pUi->addWidget(GUIReader::shareReader()->widgetFromJsonFile("./Data/UIPVE_1/UIPVE_1.ExportJson"));
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
	//getWidgetByName("leftward")->addTouchEventListener(this, toucheventselector(PVEUI::onLeftTouched));
	//getWidgetByName("forward")->addTouchEventListener(this, toucheventselector(PVEUI::onForwardTouched));
	//getWidgetByName("backward")->addTouchEventListener(this, toucheventselector(PVEUI::onBackwardTouched));
	//getWidgetByName("rightward")->addTouchEventListener(this, toucheventselector(PVEUI::onRightwardTouched));
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
