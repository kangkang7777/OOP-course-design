#include "GameScene.h"

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

bool GameScene::init()
{
	// 若init失败
	if (!Scene::init())
	{
		return false;
	}

	//生成背景
	auto map = Sprite::create("background.jpg");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(0, 0);
	this->addChild(map, 0);

	//生成玩家
	player = CCSprite::create("player.png");
	player->setPosition(1920, 1080);
	this->addChild(player, 1);

	//视角跟随
	auto s = Director::getInstance()->getWinSize();
	this->runAction(Follow::create(player, Rect(0, 0, s.width * 3, s.height*3)));

	//鼠标监听&操控
	auto m_listener = EventListenerTouchOneByOne::create();
	m_listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
	steer = Sprite::create("steer.png");
	steer->setPosition(Vec2(0, 0));
	steer->setOpacity(1);
	this->addChild(steer, 1);

	//键盘监听&注册
	auto k_listener = EventListenerKeyboard::create();
	k_listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	k_listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(k_listener, this);

	//时间表
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::borderControl), 0.1f);

	return true;
}

//
void GameScene::update(float delta)
{
	Node::update(delta);
	keyPressedDuration();
}

// trigger when moving touch
bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	
	_start_center_Point = touch->getLocationInView();
	//创建方向盘
	steer->setOpacity(200);
	steer->setPosition(Vec2(_start_center_Point));
	
	return true;
}
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

//键盘操作
void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	keys[keycode] = true;
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	keys[keycode] = false;
}
bool GameScene::isKeyPressed(EventKeyboard::KeyCode keyCode)
{
	return keys[keyCode];
}
void GameScene::keyPressedDuration()
{
	const int moveDistance = 5;
	var_x = 0, var_y = 0;
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	auto rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW;
	auto downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	if (keys[leftArrow])
		var_x = -moveDistance;
	else if (keys[rightArrow])
		var_x = moveDistance;
    if (keys[upArrow])
		var_y = moveDistance;
	else if (keys[downArrow])
		var_y = -moveDistance;
	auto moveTo = MoveBy::create(0.5, Vec2(var_x, var_y));
	player->runAction(moveTo);
}

void GameScene::borderControl(float fDelta)
{
	int control_x = 0, control_y = 0;
	if (player->getPosition().x < 0)
		control_x += 3839;
	else if(player->getPosition().x > 3840)
		control_x -= 3839;
	if (player->getPosition().y < 0)
		control_y += 2159;
	else if (player->getPosition().y > 2160)
		control_y -= 2159;
	auto move_control = MoveBy::create(1.0/60, Vec2(control_x, control_y));
	player->runAction(move_control);
}

//
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
