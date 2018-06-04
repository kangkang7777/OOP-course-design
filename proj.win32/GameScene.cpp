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


	auto myMouseListener = EventListenerTouchOneByOne::create();//创建事件监听器鼠标事件
	//lambda expression
	//鼠标被按下

	//myMouseListener->onTouchBegan = [=](Event *event)
	//{
	//	
	//	EventMouse* e = (EventMouse*)event;
	//	//mouse_down_x = e->getCursorX();
	//	//mouse_down_y = visibleSize.height + e->getCursorY();

	//};
	////鼠标按键移动
	//myMouseListener->onMouseMove = [=](Event *event)
	//{
	//	float mouse_move_x, mouse_move_y,
	//		mouse_down_x, mouse_down_y;
	//	EventMouse* e = (EventMouse*)event;
	//	mouse_move_x = e->getCursorX();
	//	mouse_move_y = visibleSize.height + e->getCursorY();
	//	mouse_down_x = getPreviousLocation();

	//	auto moveBy = MoveBy::create(1, Vec2(mouse_move_x - mouse_down_x,
	//		mouse_move_y - mouse_down_y));
	//	player->runAction(moveBy);
	//};
	myMouseListener->onTouchBegan = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//Point startPoint = touch->getLocation();
		return true; // if you are consuming it
	};
	
	myMouseListener->onTouchMoved = [](Touch* touch, Event* event)
	{
		
		// trigger when moving touch
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		float x0 = touch->getStartLocation().x;
		float y0 = touch->getStartLocation().y;
		
		//auto steer = Sprite::create("steer.png");
		//steer->setPosition(Vec2(x0, y0));
		//->addChild(steer, 2);
		//如果在园外 则为一倍速度 在园内 实际速度
		float x1 = touch->getLocation().x;
		float y1 = touch->getLocation().y;
		
		float unitization = sqrt((x1 - x0)*(x1 - x0) +
			                     (y1 - y0)*(y1 - y0));
		float movePointX, movePointY;
		if (unitization != 0)
		{
			movePointX = (x1 - x0) / unitization * 5;
			movePointY = (y1 - y0) / unitization * 5;
		}
		else
		{
			movePointX = 0;
			movePointY = 0;
		}
		auto moveTo = MoveBy::create(5, Vec2(movePointX, movePointY));
		target->runAction(moveTo);
	};

	// trigger when you let up
	myMouseListener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
	};


	//注册与绑定 监听
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, player);


	return true;
}


void GameScene::background()
{
	auto map = Sprite::create("background.jpg");
	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(0, 0);
	this->addChild(map, 0);
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
