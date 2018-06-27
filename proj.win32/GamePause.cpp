#include "Gamepause.h"  


Scene* GamePause::createScene()
{
	return GamePause::create();
}

bool GamePause::init()
{

	if (!Scene::init())
	{
		return false;
	}
	//得到窗口的大小  
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//原点坐标  
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	auto button1 = Button::create();
	button1->setTitleText("restart game");
	button1->setPosition(Vec2(640,500));
	button1->setTitleFontSize(32);
	button1->setTouchEnabled(true);
	button1->addTouchEventListener(CC_CALLBACK_1(GamePause::ContinueCallback, this));
	this->addChild(button1);

	auto button2 = Button::create();
	button2->setTitleText("Exit game");
	button2->setPosition(Vec2(640, 400));
	button2->setTitleFontSize(32);
	button2->setTouchEnabled(true);
	this->addChild(button2);
	button2->addTouchEventListener(CC_CALLBACK_1(GamePause::ExitCallback, this));

	auto button3 = Button::create();
	button3->setTitleText("Back to menu");
	button3->setPosition(Vec2(640, 300));
	button3->setTitleFontSize(32);
	button3->setTouchEnabled(true);
	this->addChild(button3);
	button3->addTouchEventListener(CC_CALLBACK_1(GamePause::menuCallback, this));
	return true;
}
void GamePause::ContinueCallback(CCObject* pSender)
{
      CCDirector::sharedDirector()->pushScene(GameScene::createScene());
}

void GamePause::ExitCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void GamePause::menuCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popToRootScene();
}