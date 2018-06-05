#include "GameScene.h"
#include "math.h"
auto visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();
Scene* GameScene::createScene()
{
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	//生成背景
	GameScene::background();

	//创建玩家
	auto player = CCSprite::create("player.png");
	player->setPosition(640, 360);
	this->addChild(player, 1);
	//视角跟随
	auto s = Director::getInstance()->getWinSize();
	this->runAction(Follow::create(player, Rect(0, 0, s.width * 3, s.height*3)));

}



void GameScene::menuCloseCallback(Ref* pSender)
{
	//返回菜单界面，出栈
	Director::getInstance()->pushScene(TransitionFade::create(3.0f,GameScene::createScene()));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}
