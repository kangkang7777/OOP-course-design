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
	player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(player, 1);

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	
	
	auto m_listener = EventListenerTouchOneByOne::create();
	m_listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	steer = Sprite::create("steer.png");
	steer->setPosition(Vec2(0, 0));
	steer->setOpacity(1);
	this->addChild(steer, 1);
	return true;
}



void GameScene::background()
{
	auto map = Sprite::create("background.jpg");
	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(0, 0);
	
	this->addChild(map, 0);
}


bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	
	_start_center_Point = touch->getLocationInView();
	//创建方向盘
	steer->setOpacity(200);
	steer->setPosition(Vec2(_start_center_Point));
	
	return true;
}
// trigger when moving touch
void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//start point
	float x0 = _start_center_Point.x;
	float y0 = _start_center_Point.y;
	//->addChild(steer, 2);
	//如果在园外 则为一倍速度 在园内 实际速度
	float x1 = touch->getLocationInView().x;
	float y1 = touch->getLocationInView().y;

	float norm = sqrt((x1 - x0)*(x1 - x0) +
		(y1 - y0)*(y1 - y0));
	float movePointX, movePointY;
	if (norm != 0)
	{
		movePointX = (x1 - x0) / norm * 5;
		movePointY = (y1 - y0) / norm * 5;
	}
	else
	{
		movePointX = 0;
		movePointY = 0;
	}
	auto moveTo = MoveBy::create(5, Vec2(movePointX, movePointY));
	target->runAction(moveTo);
	
}
void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	//hide the steer
	steer->setOpacity(1);
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
