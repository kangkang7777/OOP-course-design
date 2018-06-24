#include "GameLayer.h"

enum GameLayerZOrder
{
	GAME_LAYER_BACKGROUND_Z,
	GAME_LAYER_MAP_Z,
	GAME_LAYER_SPRITE_Z,
};

GameLayer::GameLayer()
{
	
}

GameLayer::~GameLayer()
{
	_rival.clear();
	_food.clear();
	_prick.clear();
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto colorLayer = LayerColor::create(Color4B(49, 49, 49, 255), DESIGN_SCREEN_WIDTH, DESIGN_SCREEN_HEIGHT);
	this->addChild(colorLayer, GAME_LAYER_BACKGROUND_Z);

	_map = Node::create();
	_map->setContentSize(Size(MAP_WIDTH, MAP_HEIGHT));
	this->addChild(_map, GAME_LAYER_MAP_Z);

	initDataDefault();

	this->scheduleUpdate();
	this->scheduleOnce(schedule_selector(GameLayer::startAddPrick), 3);
	this->schedule(schedule_selector(GameLayer::randomResetFoods), 2);
    this->schedule(schedule_selector(GameLayer::updaterivalmove), 0.5);
	this->schedule(schedule_selector(GameLayer::scoreRank), 2);
	this->schedule(schedule_selector(GameLayer::timeCountDown), 1);
	//键盘监听&注册
	auto k_listener = EventListenerKeyboard::create();
	k_listener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
	k_listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(k_listener, this);
	
	//
	
	//鼠标
	_Njoystick = Node::create();
	_Njoystick->setContentSize(Size(100, 100));
	this->addChild(_Njoystick);

	_joystick = Sprite::create("joystick.png");
	_Njoystick->addChild(_joystick);
	//先不显示
	_joystick->setVisible(false);
	_joySteer = Sprite::create("joysteer.png");
	_Njoystick->addChild(_joySteer);
	_joySteer->setVisible(false);

	auto m_listener = EventListenerTouchOneByOne::create();
	m_listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
	
	//

	//分数榜
	_scoreBoard = Node::create();
	_scoreBoard->setContentSize(Size(200, 200));
	_scoreBoard->setAnchorPoint(Point(1, 1));
	_scoreBoard->setPosition(1280, 900);
	this->addChild(_scoreBoard, 4);

	label1 = Label::createWithSystemFont("N/A", "Arial", 25);
	label1->setPosition(0, 0);
	_scoreBoard->addChild(label1);
	label2 = Label::createWithSystemFont("N/A", "Arial", 25);
	label2->setPosition(0, -30);
	_scoreBoard->addChild(label2);
	label3 = Label::createWithSystemFont("N/A", "Arial", 25);
	label3->setPosition(0, -60);
	_scoreBoard->addChild(label3);
	labelMy = Label::createWithSystemFont("N/A", "Arial", 25);
	labelMy->setPosition(0, -90);
	_scoreBoard->addChild(labelMy);

	//倒计时
	_timeLabel = Label::createWithSystemFont("XX:XX:XX", "Arial", 30);
	_timeBoard = Node::create();
	_timeBoard->setContentSize(Size(200, 200));
	_timeBoard->setAnchorPoint(Point(1, 1));
	_timeBoard->setPosition(800, 900);
	this->addChild(_timeBoard);
	_timeBoard->addChild(_timeLabel, 4);
	_timeLabel->setPosition(0, 0);
	return true;
}

void GameLayer::update(float dt)
{
	updateFoods();
	updatePrick();
	_player->updateDivision();
	updateRival();
	updateView();
	collideRival(); 
	updateonExit();

	//updateplayermove_touch(_player);
	updateplayermove_key(_player);
}

void GameLayer::timeCountDown(float dt)
{
	maxTime -= 1;
	_timeLabel->setString(StringUtils::format("%d : %d", maxTime / 60, maxTime % 60));
}

//键盘操作
void GameLayer::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	keys[keycode] = true;
}
void GameLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	keys[keycode] = false;
}
bool GameLayer::isKeyPressed(EventKeyboard::KeyCode keyCode)
{
	return keys[keyCode];
}

void GameLayer::scoreRank(float dt)
{
	Vector<Player *> rank;
	for (auto item : _rival)
	{
		rank.pushBack(item.second);
	}
	rank.pushBack(_player);

	for (int i = 0; i<rank.size(); i++)
	{
		for (int j = rank.size() - 1; j>i; j--)
		{
			Player * player1 = rank.at(j);
			Player * player2 = rank.at(j - 1);
			int score1 = player1->getTotalScore();
			int score2 = player2->getTotalScore();
			if (score1 > score2)
			{
				rank.swap(j, j - 1);
			}
		}
	}
	label1->setString("1: " + rank.at(0)->getPlayerName() + " score: "
		+ StringUtils::format("%d", rank.at(0)->getTotalScore()));

	label2->setString("2: " + rank.at(1)->getPlayerName() + " score: "
		+ StringUtils::format("%d", rank.at(1)->getTotalScore()));

	label3->setString("3: " + rank.at(2)->getPlayerName() + " score: "
		+ StringUtils::format("%d", rank.at(2)->getTotalScore()));

	labelMy->setString("YOU: " +_player->getPlayerName() + " score: "
		+ StringUtils::format("%d", _player->getTotalScore()));
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
	_joystick->setVisible(true);
	_joystick->setPosition(touch->getStartLocation());
	return true;
}
void GameLayer::onTouchMoved(Touch *touch, Event *event)
{
	//如果在园外 则为一倍速度 在园内 实际速度
	_touchEventVec = (touch->getLocation() - touch->getStartLocation()).getNormalized();
	_joySteer->setVisible(true);
	_joySteer->setPosition(touch->getStartLocation() + _touchEventVec * 45);
}
void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
	_touchEventVec = Vec2::ZERO;
	_joystick->setVisible(false);
	_joySteer->setVisible(false);
}

//角色初始化(玩家)
void GameLayer::initPlayer()
{
	//随机出现
	float xPosition = rand() % MAP_WIDTH;
	float yPosition = rand() % MAP_HEIGHT;
	_player = Player::create(Vec2(xPosition, yPosition), _map);
	_player->setLocalZOrder(_player->getTotalScore());
	_map->addChild(_player);
	//视角跟随主角
	//auto s = Director::getInstance()->getWinSize();
	//_map->runAction(Follow::create(_player, Rect(0, 0, s.width * 3, s.height * 3)));

}

//敌人初始化(AI)
void GameLayer::initRival()
{
	for (int i = 0,j = 1,m = 1; i < MAX_RIVAL_NUM; i++,j++,m++)
	{
		if (j == 3)
			j = 1;
		if (m == 8)
			m = 1;
		float positionX =Random(0, MAP_WIDTH);
		float positionY =Random(0, MAP_HEIGHT);
		auto rival = Player::create(Vec2(positionX, positionY), name[i], j, m, _map);
		rival->setLocalZOrder(rival->getTotalScore());
		_map->addChild(rival);
		_rival.insert(StringUtils::format("%d", i ), rival);
	}
}

//食物初始化
void GameLayer::initFoods()
{
	int count = 0;
	for (int _x = 100; _x < MAP_WIDTH-100; _x+=100)
	{
		for (int _y = 100; _y < MAP_HEIGHT-100; _y +=100)
		{
			    int type = Random(1, 4);
			    int color = Random(1, 6);
				std::string path = StringUtils::format("gameScene/food%d_%d.png", type, color);
				auto food = Foods::create(path.c_str());

				food->setPosition(Vec2(_x + Random(-100, 100), _y + Random(-100, 100)));
				food->setLocalZOrder(food->getScore());
				_map->addChild(food);
				_food.pushBack(food);
		}
	}
}

//刺球初始化
void GameLayer::initPrick()
{
	for (int i = 0; i < INIT_PRICK_NUM; i++)
	{
		Prick * prick = Prick::create("gameScene/prick.png");
		int x = Random(0,MAP_WIDTH);
		int y = Random(0,MAP_HEIGHT);
		prick->setPosition(x, y);
		_map->addChild(prick, prick->getScore());
		_prick.pushBack(prick);
	}
}

//刺球添加
void GameLayer::startAddPrick(float dt)
{
	this->schedule(schedule_selector(GameLayer::addPrick), 5);
}

void GameLayer::addPrick(float dt)
{
	Prick * prick = Prick::create("gameScene/prick.png");
	int xPosition = rand() % MAP_WIDTH;
	int yPosition = rand() % MAP_HEIGHT;
	prick->setPosition(Vec2(xPosition, yPosition));
	prick->setLocalZOrder(prick->getScore());
	_map->addChild(prick);
	_prick.pushBack(prick);
}


//player移动
void GameLayer::updateplayermove_key(Player * player)
{
	float var_x = 0, var_y = 0;
	const float moveDistance = 2;
	auto leftArrow_1 = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	auto rightArrow_1 = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto upArrow_1 = EventKeyboard::KeyCode::KEY_UP_ARROW;
	auto downArrow_1 = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	auto leftArrow_2 = EventKeyboard::KeyCode::KEY_A;
	auto rightArrow_2 = EventKeyboard::KeyCode::KEY_D;
	auto upArrow_2 = EventKeyboard::KeyCode::KEY_W;
	auto downArrow_2 = EventKeyboard::KeyCode::KEY_S;
	if (keys[leftArrow_1]|| keys[leftArrow_2])
		var_x = -moveDistance;
	else if (keys[rightArrow_1]|| keys[rightArrow_2])
		var_x = moveDistance;
	if (keys[upArrow_1]|| keys[upArrow_2])
		var_y = moveDistance;
	else if (keys[downArrow_1]|| keys[downArrow_2])
		var_y = -moveDistance;
	if (var_x == 0 && var_y == 0)
	{
		player->setConcentrate();
	}
	else
	{
		Vec2 vec(var_x, var_y);
		player->setVec(vec);
	}
}

void GameLayer::updateplayermove_touch(Player * player)
{
	if(_touchEventVec==Vec2(0,0))
		player->setConcentrate();
	else
	    player->setVec(_touchEventVec);
}

void GameLayer::updaterivalmove(float dt)
{
	for (auto item : _rival)
	{
		auto rival = item.second;
		if (rival == NULL&&Random(0,1))
		{
			break;
		}
		
		Vec2 Rand(Random(-5, 5), Random(-5, 5));
		Vec2 vec = _player->getPosition() - rival->getPosition() + Rand;
		vec.normalize();
		vec = vec *1.5;
		if (rival->getTotalWeight() > _player->getTotalWeight()*MIN_CHASE_MULTIPLE)
		{
			rival->setVec(vec);
		}
		else if (_player->getTotalWeight() > rival->getTotalWeight()*MIN_CHASE_MULTIPLE)
		{
			rival->setVec(-vec);
		}
		else
		{
			rival->setConcentrate();
		}
	}
}

void GameLayer::updateView()
{
	auto rect = _player->getPlayerRect();

	float scaleX = DESIGN_SCREEN_WIDTH / (DESIGN_SCREEN_WIDTH + rect.size.width);
	float scaleY = DESIGN_SCREEN_HEIGHT / (DESIGN_SCREEN_HEIGHT + rect.size.height);
	_mapScale = (scaleX < scaleY) ? scaleX : scaleY;

	float dx = rect.origin.x*_mapScale - DESIGN_SCREEN_WIDTH / 2;
	float dy = rect.origin.y*_mapScale - DESIGN_SCREEN_HEIGHT / 2;

	Vec2 newPosition = Vec2(-dx, -dy);

	_map->setScale(_mapScale);
	_map->setPosition(newPosition);
}

void GameLayer::updateFoods()
{
	collideFoods(_player);
	for (auto item : _rival)
	{
		auto rival = item.second;
		if (rival != NULL)
		{
			collideFoods(rival);
		}
	}
}

void GameLayer::collideFoods(Player * player)
{
	//对每个food 检测碰撞
	for (auto food : _food) 
	{
		if (food->isVisible())
		{
			if (player->collideFoods(food))
			{
				food->setVisible(false);
				float time = rand() % 10 + 10;//食物再次出现的Δt
				break;
			}
		}

	}
}

void GameLayer::randomResetFoods(float dt)
{
	for (auto food : _food)
	{
		if (!food->isVisible() && !Random(0, 10))
		{
			food->setVisible(true);
		}
	}
}

void GameLayer::updatePrick()
{
	collidePrick(_player);
	for (auto item : _rival)
	{
		auto rival = item.second;
		if (rival != NULL)
		{
			collidePrick(rival);
		}
	}
}

void GameLayer::collidePrick(Player * player)
{
	for (auto prick : _prick)
	{
		if (prick->isVisible()&& prick != NULL && player->collidePrick(prick))
		{
			prick->setVisible(false);
			break;
		}
	}
}

void GameLayer::updateRival()
{
	for (auto item : _rival)
	{
		auto rival = item.second;
		if (rival != NULL)
		{
			//rival->AI(m_map, m_sporeArray);
			rival->updateDivision();
		}
	}
}

//检测玩家与敌人的碰撞
void GameLayer::collideRival()
{
	for (auto item : _rival)        
	{
		auto rival = item.second;
		if (rival != NULL)
		{
			if (_player->collideRival(rival))
			{
				float playerDivisionCount = _player->getDivisionNum();
				if (playerDivisionCount == 0)
				{
					_player->resetPlayer();
					break;
				}
			}
		}
	}

	for (auto item1 : _rival)
	{
		auto rival1 = item1.second;

		if (rival1 != NULL)
		{
			for (auto item2 : _rival)
			{
				auto rival2 = item2.second;
				if (rival2 != NULL && item1 != item2)
				{
					if (rival1->collideRival(rival2))
					{
						float rival1DivisionCount = rival1->getDivisionNum();
						float rival2DivisionCount = rival2->getDivisionNum();
						if (rival1DivisionCount == 0)
						{
							rival1->resetPlayer();
							break;
						}

						if (rival2DivisionCount == 0)
						{
							rival2->resetPlayer();
						}
					}
				}
			}
		}

	}
}

void GameLayer::resetFoods(Node * node)
{
	node->setVisible(true);
}

void GameLayer::resetPlayer()
{

}

void GameLayer::onExit()
{
	this->unscheduleAllCallbacks();
	Layer::onExit();
}

void GameLayer::updateonExit()
{
	static int flag = 1;
	auto ESC = EventKeyboard::KeyCode::KEY_ESCAPE;
	if (keys[ESC])
	{
		Director::getInstance()->pushScene(Gamepause::createScene());
		//Director::getInstance()->replaceScene(Gamepause::createScene());
		//Director::getInstance()->popScene();
		flag=2;
	}

}

void GameLayer::initDataDefault()
{
	initRival();
	initPlayer();
	initFoods();
	initPrick();
}

