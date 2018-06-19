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
	Player *player1 = Player::create(Vec2(1920,1080),"player.png");
	//player1->setPosition(1920, 1080);
	//this->addChild(player1, 1);

	player=Sprite::create("player.png");
	player->setPosition(1920, 1080);
	this->addChild(player, 1);

	//食物初始化
	foodGenerate();

	//生成流星锤

	//视角跟随
	auto s = Director::getInstance()->getWinSize();
	this->runAction(Follow::create(player, Rect(0, 0, s.width * 3, s.height*3)));

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

//边界控制
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

//食物
void GameScene::foodGenerate()
{
	int count = 0;
	for(int _x=10;_x<3840;_x+=100)
	    for (int _y = 10; _y<2160; _y += 100)
	    {
			//foods[count] = Sprite::create("bean_polygon3_2.png");
			//foods[count]->setScale(0.3, 0.3);
			//foods[count] ->setPosition(_x + Random(-100, 100), _y + Random(-100, 100));
		    int type = Random(3,6);
			int color = Random(1, 6);
			std::string path = StringUtils::format("bean_polygon%d_%d.png", type, color);
			foods[count] = Sprite::create(path.c_str());
			foods[count]->setScale(0.3, 0.3);
			foods[count] ->setPosition(_x + Random(-100, 100), _y + Random(-100, 100));
			this->addChild(foods[count++], 0);
	    }
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
