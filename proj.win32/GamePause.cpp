#include "Gamepause.h"  


Scene* Gamepause::createScene()
{
	return Gamepause::create();
}

bool Gamepause::init()
{

	if (!Scene::init())
	{
		return false;
	}
	//得到窗口的大小  
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//原点坐标  
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	/*
	//继续游戏按钮  
	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"pause_continue.png",
		"pause_continue.png",
		this,
		menu_selector(Gamepause::menuContinueCallback));

	pContinueItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 30));
	
	CCMenu* pMenu = CCMenu::create(pContinueItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);
	*/
	auto button1 = Button::create();
	button1->setTitleText("restart game");
	button1->setPosition(Vec2(640,500));
	button1->setTitleFontSize(32);
	button1->setTouchEnabled(true);
	button1->addTouchEventListener(CC_CALLBACK_1(Gamepause::ContinueCallback, this));
	this->addChild(button1);

	auto button2 = Button::create();
	button2->setTitleText("Exit game");
	button2->setPosition(Vec2(640, 400));
	button2->setTitleFontSize(32);
	button2->setTouchEnabled(true);
	this->addChild(button2);
	button2->addTouchEventListener(CC_CALLBACK_1(Gamepause::ExitCallback, this));

	auto button3 = Button::create();
	button3->setTitleText("Back to menu");
	button3->setPosition(Vec2(640, 300));
	button3->setTitleFontSize(32);
	button3->setTouchEnabled(true);
	this->addChild(button3);
	button3->addTouchEventListener(CC_CALLBACK_1(Gamepause::menuCallback, this));
	return true;
}
void Gamepause::ContinueCallback(CCObject* pSender)
{
      CCDirector::sharedDirector()->pushScene(GameScene::createScene());
	//CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
}

void Gamepause::ExitCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void Gamepause::menuCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popToRootScene();
}