#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// 退出按钮 add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}
	//开始按钮

	//auto StartGame = Button::create("StartNormal.png", "StartSelected.png", "StartSelected.png");
	auto StartGame = Button::create();
	StartGame->setTouchEnabled(true);
	StartGame->setTitleText("Start Game");
	StartGame->setTitleFontSize(32);
	StartGame->setPosition(Vec2(640,160));
	this->addChild(StartGame,10);
	
	

	// create exit menu, it's an autorelease object
	auto menu_exit = Menu::create(closeItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	menu_exit->setPosition(Vec2(0,0));
	this->addChild(menu_exit, 1);


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows the words
	// create and initialize a label

	//auto label = Label::createWithTTF("球球大作战", "fonts/Marker Felt.ttf", 36);
	//if (label == nullptr)
	//{
	//	problemLoading("'fonts/Marker Felt.ttf'");
	//}
	//else
	//{
		// position the label on the center of the screen
	//	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//		origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
	//	this->addChild(label, 1);
	//}

	// add "MenuScene" splash screen"
	auto sprite = Sprite::create("MenuScene.png");
	if (sprite == nullptr)
	{
		problemLoading("'MenuScene.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}
	return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}


void MenuScene::gameStartCallback(Ref* pSender)
{
	//场景跳转至正式游戏界面
//	Director::getInstance()->runWithScene(GameScene::createScene());
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}