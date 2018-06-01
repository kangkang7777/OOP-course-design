#include "GameScene.h"

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

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

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
	//生成背景
	GameScene::background();

	//create a player
	auto player = CCSprite::create("player.png");
	player->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(player, 1);

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto myMouseListener = EventListenerMouse::create();//创建事件监听器鼠标事件
	//lambda expression
	//鼠标被按下
	extern float mouse_down_x, mouse_down_y, mouse_up_x, mouse_up_y;
	myMouseListener->onMouseDown = [=](Event *event)
	{
		EventMouse* e = (EventMouse*)event;
		mouse_down_x = e->getCursorX();
		mouse_down_y = e->getCursorY();
	};
	//鼠标移动
	myMouseListener->onMouseMove = [=](Event *event)
	{
		

	};
	//鼠标按键弹起
	myMouseListener->onMouseUp = [=](Event *event)
	{
		EventMouse* e = (EventMouse*)event;
		mouse_up_x = e->getCursorX();
		mouse_up_y = e->getCursorY();
		
	};

	//将事件监听器与场景绑定
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);
	return true;
}


void GameScene::background()
{
	auto map = Sprite::create("background.jpg");
	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(0, 0);
	this->addChild(map, 0);
}

void GameScene::Player()
{
	
}

void GameScene::move()
{
	//player->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

}

void GameScene::menuCloseCallback(Ref* pSender)
{
	//返回菜单界面，出栈
	Director::getInstance()->popScene();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}
