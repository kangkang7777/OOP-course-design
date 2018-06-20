#include "GameLayer.h"
//#include "Tools/Joystick/Joystick.h"

//#include "../SceneManager.h"

enum GameLayerZOrder
{
	GAME_LAYER_BACKGROUND_Z,
	GAME_LAYER_MAP_Z,
	GAME_LAYER_SPRITE_Z,
	GAME_LAYER_JOYSTICK_Z
};

GameLayer::GameLayer()
{
	_roomID = -1;
}

GameLayer::~GameLayer()
{
	_rival.clear();
	_food.clear();
	_sporeMap.clear();
	_prickMap.clear();
	_eventDispatcher->removeCustomEventListeners("Divide");
	_eventDispatcher->removeCustomEventListeners("Spit");
	_eventDispatcher->removeCustomEventListeners("PlayerMove");
	_eventDispatcher->removeCustomEventListeners("PlayerDivide");
	_eventDispatcher->removeCustomEventListeners("SpitSporeResult");
	_eventDispatcher->removeCustomEventListeners("AddPrick");
	_eventDispatcher->removeCustomEventListeners("EnterPlayer");
	_eventDispatcher->removeCustomEventListeners("PlayerConcentrate");
	_eventDispatcher->removeCustomEventListeners("UpdatePlayer");
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

	initData();
	initDataDefault();
	/*
	_joystick = Joystick::create("gameScene/base.png", "gameScene/joystick.png");
	_joystick->setPosition(Vec2::ZERO);
	_joystick->setVisible(false);
	this->addChild(_joystick, GAME_LAYER_JOYSTICK_Z);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_eventDispatcher->addCustomEventListener("Divide", CC_CALLBACK_0(GameLayer::dividePlayer, this));
	_eventDispatcher->addCustomEventListener("Spit", CC_CALLBACK_0(GameLayer::spitSpore, this));
	_eventDispatcher->addCustomEventListener("PlayerMove", CC_CALLBACK_1(GameLayer::playerMoveEvent, this));
	_eventDispatcher->addCustomEventListener("PlayerDivide", CC_CALLBACK_1(GameLayer::playerDivideEvent, this));
	_eventDispatcher->addCustomEventListener("SpitSporeResult", CC_CALLBACK_1(GameLayer::spitSporeResultEvent, this));
	_eventDispatcher->addCustomEventListener("AddPrick", CC_CALLBACK_1(GameLayer::addPrickEvent, this));
	_eventDispatcher->addCustomEventListener("EnterPlayer", CC_CALLBACK_1(GameLayer::enterPlayerEvent, this));
	_eventDispatcher->addCustomEventListener("PlayerConcentrate", CC_CALLBACK_1(GameLayer::playerConcentrateEvent, this));
	_eventDispatcher->addCustomEventListener("UpdatePlayer", CC_CALLBACK_1(GameLayer::updatePlayerEvent, this));
	*/

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameLayer::updateScore), 1);
	this->schedule(schedule_selector(GameLayer::updateRank), 2);
	//this->schedule(schedule_selector(GameLayer::synPlayerInfo), 0.2);
	//this->schedule(schedule_selector(GameLayer::synPlayerMove), 0.1);
	//this->schedule(schedule_selector(GameLayer::synSporeInfo), 0.1);
	//this->scheduleOnce(schedule_selector(GameLayer::startAddPrick), 3);

	auto m_listener = EventListenerTouchOneByOne::create();
	m_listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	//键盘监听&注册
	auto k_listener = EventListenerKeyboard::create();
	k_listener->onKeyPressed = CC_CALLBACK_2(Gamelayer::onKeyPressed, this);
	k_listener->onKeyReleased = CC_CALLBACK_2(Gamelayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(k_listener, this);

	//视角跟随主角
	//不应该这样
	/*auto s = Director::getInstance()->getWinSize();
	this->runAction(Follow::create(player, Rect(0, 0, s.width * 3, s.height * 3)));*/

	return true;
}

void GameLayer::update(float dt)
{
	updateFoods();
	updateSpore();
	updatePrick();
	_player->updateDivision();
	//updateRival();        //每个玩家信息由玩家客户端自己更新
	updateView();
	collide();
	updateplayermove_key(_player);
	updateplayermove_touch(_player);
	//synPlayerInfo();
	//synPlayerMove();
	//synSporeInfo();
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{

	
	//创建方向盘
	steer->setOpacity(200);
	steer->setPosition(touch->getStartLocation());

	return true;
}
// trigger when moving touch
void GameLayer::onTouchMoved(Touch *touch, Event *event)
{

	//auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//start point

	//->addChild(steer, 2);
	//如果在园外 则为一倍速度 在园内 实际速度
	vect = (touch->getLocation() - touch->getPreviousLocation()).getNormalized();
	
	
}
void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
	//hide the steer
	steer->setOpacity(0);
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



/*
void GameLayer::initRival(rapidjson::Value &value)
{

	int size = value.Size();
	for (int i = 0; i < size; i++)
	{
		std::string accountName = value[i]["AccountName"].GetString();
		std::string gameName = value[i]["GameName"].GetString();
		int vestmentID = value[i]["VestmentID"].GetInt();
		int keywordID = value[i]["KeywordID"].GetInt();
		double vx = value[i]["vx"].GetDouble();
		double vy = value[i]["vy"].GetDouble();
		auto player = Player::create(gameName, vestmentID, keywordID, Vec2(vx, vy), _map);
		_map->addChild(player);
		_rival.insert(accountName, player);

		int divisionNum = value[i]["DivisionList"].Size();
		for (int j = 0; j < divisionNum; j++)
		{
			double x = value[i]["DivisionList"][j][0].GetDouble();
			double y = value[i]["DivisionList"][j][1].GetDouble();
			int score = value[i]["DivisionList"][j][2].GetInt();
			double vx = value[i]["DivisionList"][j][3].GetDouble();
			double vy = value[i]["DivisionList"][j][4].GetDouble();
			auto division = player->createDivision(Vec2(x, y), Vec2(vx, vy), score);
			_map->addChild(division, score);
		}
	}
}
*/
//角色初始化(玩家)
void GameLayer::initPlayer()
{
	//随机出现
	float xPosition = rand() % MAP_WIDTH;
	float yPosition = rand() % MAP_HEIGHT;
	_player = Player::create(Vec2(xPosition, yPosition), _map);
	_player->setLocalZOrder(_player->getTotalScore());
	_map->addChild(_player);
}

//敌人初始化(AI)
void GameLayer::initRival()
{
	for (int i = 0; i < MAX_RIVAL_NUM; i++)
	{
		float positionX =Random(0, DESIGN_SCREEN_WIDTH);
		float positionY =Random(0,DESIGN_SCREEN_HEIGHT);
		auto rival = Player::create(Vec2(positionX, positionY), _map);
		rival->setLocalZOrder(rival->getTotalScore());
		_map->addChild(rival);
		_rival.insert(StringUtils::format("%d", i ), rival);
	}
}

//食物初始化
void GameLayer::initFoods()
{
	int count = 0;
	for (int _x = 0; _x < MAP_WIDTH; _x+=100)
	{
		for (int _y = 0; _y < MAP_HEIGHT; _y +=100)
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
		_prickMap.insert(i, prick);
	}
}

//刺球添加
void GameLayer::startAddPrick(float dt)
{
	this->schedule(schedule_selector(GameLayer::addPrick), 5);
}
void GameLayer::addPrick(float dt)
{
	static int id = 15;
	Prick * prick = Prick::create("gameScene/prick.png");
	int xPosition = rand() % MAP_WIDTH;
	int yPosition = rand() % MAP_HEIGHT;
	prick->setPosition(Vec2(xPosition, yPosition));
	prick->setLocalZOrder(prick->getScore());
	_map->addChild(prick);
	_prickMap.insert(id, prick);
	id++;
}

/*
void GameLayer::initSpore(rapidjson::Value &value)
{
	int size = value.Size();
	for (int i = 0; i < size; i++)
	{
		int globalID = value[i][0].GetInt();
		int sporeID = value[i][1].GetInt();
		double x = value[i][2].GetDouble();
		double y = value[i][3].GetDouble();
		Spore * spore = Spore::create("public/keyword_1.png");
		spore->setPosition(x, y);
		_map->addChild(spore, spore->getScore());
		_sporeMap.insert(globalID, spore);
	}
}

*/

//player移动
void GameLayer::updateplayermove_key(Player * player)
{
	int var_x = 0, var_y = 0;
	const int moveDistance = 5;
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
	Vec2 vec(var_x, var_y);
	player->setVec(vec);
	auto moveBy = MoveBy::create(PLAYER_INITIAL_VECTOR, player->getVec());
	player->runAction(moveBy);
}

void GameLayer::updateplayermove_touch(Player * player)
{
	auto moveBy = MoveBy::create(0.5, vect);
	player->runAction(moveBy);
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
	Rect rect = player->getPlayerRect();
	Vec2 position = player->getPosition();

	Vec2 point1 = Vec2(rect.origin.x - rect.size.width / 2, rect.origin.y - rect.size.height / 2);//玩家左下角
	int divisionX1 = floor(point1.x / DESIGN_SCREEN_WIDTH);
	int divisionY1 = floor(point1.y / DESIGN_SCREEN_HEIGHT);
	int division1 = divisionY1 * MAP_DIVISION_X + divisionX1;
	Vec2 point2 = Vec2(rect.origin.x + rect.size.width / 2, rect.origin.y + rect.size.height / 2);//玩家右上角
	int divisionX2 = floor(point2.x / DESIGN_SCREEN_WIDTH);
	int divisionY2 = floor(point2.y / DESIGN_SCREEN_HEIGHT);
	int division2 = divisionY2 * MAP_DIVISION_X + divisionX2;

	//处理超出界限问题
	if (divisionX1 < 0)
	{
		divisionX1 = 0;
	}
	if (divisionY1 < 0)
	{
		divisionY1 = 0;
	}
	if (divisionX2 == MAP_DIVISION_X)
	{
		divisionX2 = MAP_DIVISION_X - 1;
	}
	if (divisionY2 == MAP_DIVISIOIN_Y)
	{
		divisionY2 = MAP_DIVISIOIN_Y - 1;
	}
	int xSpan = divisionX2 - divisionX1;
	int ySpan = divisionY2 - divisionY1;
	int max_ball = MAP_DIVISION_BEAN_NUM;

	for (int i = 0; i <= ySpan; i++)
	{
		for (int j = 0; j <= xSpan; j++)
		{
			division1 = (divisionY1 + i)*MAP_DIVISION_X + divisionX1 + j;
			for (int index = division1 * max_ball, m = 0; m < max_ball; m++)
			{
				auto food = _food.at(index);
				if (food->isVisible())
				{
					if (player->collideFoods(food))
					{
						food->setVisible(false);
						float time = rand() % 10 + 10;

						auto sequence = Sequence::create(
							DelayTime::create(time),
							CallFuncN::create(CC_CALLBACK_0(GameLayer::resetFoods, this, food)),
							NULL);
						food->runAction(sequence);
						//return;
					}
				}
				index++;
			}
		}
	}
}

void GameLayer::updateSpore()
{
	std::vector<int> vecDel;
	for (auto sporeItem : _sporeMap)
	{
		auto spore = sporeItem.second;
		if (spore != NULL)
		{
			Vec2 position = spore->getPosition();
			if (position.x<SPORE_RADIUS)
			{
				position.x = SPORE_RADIUS;
			}
			if (position.x>MAP_WIDTH - SPORE_RADIUS)
			{
				position.x = MAP_WIDTH - SPORE_RADIUS;
			}
			if (position.y<SPORE_RADIUS)
			{
				position.y = SPORE_RADIUS;
			}
			if (position.y>MAP_HEIGHT - SPORE_RADIUS)
			{
				position.y = MAP_HEIGHT - SPORE_RADIUS;
			}
			spore->setPosition(position);
			if (_player->collideSpore(spore))
			{
				vecDel.push_back(sporeItem.first);
			}
			else
			{
				for (auto item : _rival)
				{
					auto rival = item.second;
					if (rival != NULL)
					{
						if (rival->collideSpore(spore))
						{
							vecDel.push_back(sporeItem.first);
							break;
						}
					}
				}
			}
		}
	}

	for (auto key : vecDel)
	{
		auto spore = _sporeMap.at(key);
		_sporeMap.erase(key);
		spore->removeFromParentAndCleanup(true);
	}

	vecDel.clear();

}

void GameLayer::updatePrick()
{
	std::vector<int> vecDel;
	for (auto prickItem : _prickMap)
	{
		auto prick = prickItem.second;
		if (prick != NULL)
		{

			if (_player->collidePrick(prick))
			{
				vecDel.push_back(prickItem.first);
			}
			/*else
			{
			for (auto item : _rival)
			{
			auto rival = item.second;
			if (rival != NULL)
			{
			float radius = prick->getRadius();

			if (rival->collidePrick(prick))
			{
			vecDel.push_back(prickItem.first);
			break;
			}
			}
			}
			}*/
		}
	}
	/*
	for (auto key : vecDel)
	{
		auto prick = _prickMap.at(key);
		_prickMap.erase(key);
		prick->removeFromParentAndCleanup(true);

		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Document::AllocatorType & allocator = doc.GetAllocator();

		doc.AddMember("MsgType", MessageType::eMsg_EAT_PRICK, allocator);
		doc.AddMember("RoomID", _roomID, allocator);
		doc.AddMember("GlobalID", key, allocator);

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
		doc.Accept(write);

		std::string msg = buffer.GetString();
		WebSocketManager::getInstance()->sendMsg(msg);
	}
	vecDel.clear();
	*/
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

void GameLayer::updateRank(float dt)
{
	Vector<Player *> vec;
	for (auto item : _rival)
	{
		vec.pushBack(item.second);
	}

	vec.pushBack(_player);

	for (int i = 0; i<vec.size(); i++)
	{
		for (int j = vec.size() - 1; j>i; j--)
		{
			Player * player1 = vec.at(j);
			Player * player2 = vec.at(j - 1);
			float score1 = player1->getTotalScore();
			float score2 = player2->getTotalScore();
			if (score1 > score2)
			{
				vec.swap(j, j - 1);
			}
		}
	}

	_eventDispatcher->dispatchCustomEvent("RankChange", &vec);

}

void GameLayer::updateScore(float dt)
{
	int score = _player->getTotalScore();

	_eventDispatcher->dispatchCustomEvent("ScoreChange", &score);
}

//检测玩家与敌人的碰撞
void GameLayer::collide()
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

	/*for (auto item1 : _rival)
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
	
	}*/
}
/*
void GameLayer::spitSpore()
{
	int sporeCount = _player->countSpitSporeNum();

	std::string accountName = WebSocketManager::getInstance()->getAccountName();

	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType & allocator = doc.GetAllocator();

	doc.AddMember("MsgType", MessageType::eMsg_SPIT_SPORE, allocator);
	doc.AddMember("AccountName", rapidjson::Value(accountName.c_str(), allocator), allocator);
	doc.AddMember("RoomID", _roomID, allocator);
	doc.AddMember("SporeCount", sporeCount, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
	doc.Accept(write);

	std::string msg = buffer.GetString();
	WebSocketManager::getInstance()->sendMsg(msg);
}

void GameLayer::dividePlayer()
{
	_player->dividePlayer();

	std::string accountName = WebSocketManager::getInstance()->getAccountName();

	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType & allocator = doc.GetAllocator();

	doc.AddMember("MsgType", MessageType::eMsg_DIVIDE, allocator);
	doc.AddMember("AccountName", rapidjson::Value(accountName.c_str(), allocator), allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
	doc.Accept(write);

	std::string msg = buffer.GetString();
	//WebSocketManager::getInstance()->sendMsg(msg);
}
*/
void GameLayer::resetFoods(Node * node)
{
	node->setVisible(true);
}

void GameLayer::resetPlayer()
{

}
/*
void GameLayer::synPlayerInfo()
{
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType & allocator = doc.GetAllocator();
	rapidjson::Value divisionArr(rapidjson::kArrayType);

	Vector<PlayerDivision *> divisionList = _player->getDivisionList();
	for (auto division : divisionList)
	{
		rapidjson::Value arr(rapidjson::kArrayType);
		Vec2 position = division->getPosition();
		int score = division->getScore();
		//arr.PushBack(rapidjson::Value(StringUtils::format("%.2f", position.x).c_str(), allocator), allocator);
		//arr.PushBack(rapidjson::Value(StringUtils::format("%.2f", position.y).c_str(), allocator), allocator);
		arr.PushBack(position.x, allocator);
		arr.PushBack(position.y, allocator);
		arr.PushBack(score, allocator);
		divisionArr.PushBack(arr, allocator);
	}

	std::string accountName = WebSocketManager::getInstance()->getAccountName();
	std::string gameName = _player->getPlayerName();
	Vec2 v = _player->getVec();

	doc.AddMember("AccountName", rapidjson::Value(accountName.c_str(), allocator), allocator);
	doc.AddMember("GameName", rapidjson::Value(gameName.c_str(), allocator), allocator);
	doc.AddMember("vx", v.x, allocator);
	doc.AddMember("vy", v.y, allocator);
	doc.AddMember("DivisionList", divisionArr, allocator);
	doc.AddMember("RoomID", _roomID, allocator);
	doc.AddMember("MsgType", MessageType::eMsg_UPDATE_POSITION, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
	doc.Accept(write);

	std::string msg = buffer.GetString();
	//log("sysPlayerInfo msg::%s", msg.c_str());
	WebSocketManager::getInstance()->sendMsg(msg);
}
*/
void GameLayer::onExit()
{
	this->unscheduleAllCallbacks();
	Layer::onExit();
}

void GameLayer::initDataDefault()
{
	initRival();
	initPlayer();
	initFoods();
}
/*
void GameLayer::playerMoveEvent(EventCustom * event)
{
	char * msg = (char *)event->getUserData();
	rapidjson::Document doc;
	doc.Parse<0>(msg);
	if (doc.HasParseError())
	{
		log("GetParseError %d\n", doc.GetParseError());
		return;
	}

	if (doc.IsObject())
	{
		std::string accountName = doc["AccountName"].GetString();
		double vx = doc["vx"].GetDouble();
		double vy = doc["vy"].GetDouble();
		auto rival = _rival.at(accountName);
		if (rival != NULL)
		{
			rival->setVec(Vec2(vx, vy));
		}
	}
}

void GameLayer::playerDivideEvent(EventCustom * event)
{
	char * msg = (char *)event->getUserData();
	rapidjson::Document doc;
	doc.Parse<0>(msg);
	if (doc.HasParseError())
	{
		log("GetParseError %d\n", doc.GetParseError());
		return;
	}

	if (doc.IsObject())
	{
		std::string accountName = doc["AccountName"].GetString();
		auto rival = _rival.at(accountName);
		if (rival != NULL)
		{
			rival->dividePlayer();
		}
	}
}

void GameLayer::addPrickEvent(EventCustom * event)
{
	char * msg = (char *)event->getUserData();
	rapidjson::Document doc;
	doc.Parse<0>(msg);
	if (doc.HasParseError())
	{
		log("GetParseError %d\n", doc.GetParseError());
		return;
	}

	if (doc.IsObject())
	{
		int globalID = doc["GlobalID"].GetInt();
		int x = doc["X"].GetInt();
		int y = doc["Y"].GetInt();
		Prick * prick = Prick::create("gameScene/prick.png");
		prick->setPosition(Vec2(x, y));
		prick->setLocalZOrder(prick->getScore());
		_map->addChild(prick);
		_prickMap.insert(globalID, prick);
	}
}

void GameLayer::synSporeInfo()
{
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType & allocator = doc.GetAllocator();
	rapidjson::Value arr(rapidjson::kArrayType);

	if (_vecSporeNeedUpdate.size() == 0)
	{
		return;
	}

	for (int i = 0; i < _vecSporeNeedUpdate.size(); i++)
	{
		int key = _vecSporeNeedUpdate[i];
		auto spore = _sporeMap.at(key);
		if (spore != NULL)
		{
			if (spore->getActionManager()->getNumberOfRunningActionsInTarget(spore))
			{
				Vec2 position = spore->getPosition();
				int id = spore->getID();

				rapidjson::Value tmpArr(rapidjson::kArrayType);
				tmpArr.PushBack(key, allocator);
				tmpArr.PushBack(id, allocator);
				tmpArr.PushBack(position.x, allocator);
				tmpArr.PushBack(position.y, allocator);
				arr.PushBack(tmpArr, allocator);
			}
			else
			{
				_vecSporeNeedUpdate.erase(_vecSporeNeedUpdate.begin() + i);
				i--;
			}
		}
	}

	doc.AddMember("MsgType", MessageType::eMsg_UPDATE_SPORE, allocator);
	doc.AddMember("SporeList", arr, allocator);
	doc.AddMember("RoomID", _roomID, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
	doc.Accept(write);

	std::string msg = buffer.GetString();
	WebSocketManager::getInstance()->sendMsg(msg);
}

void GameLayer::spitSporeResultEvent(EventCustom * event)
{
	char * msg = (char *)event->getUserData();
	rapidjson::Document doc;
	doc.Parse<0>(msg);
	if (doc.HasParseError())
	{
		log("GetParseError %d\n", doc.GetParseError());
		return;
	}

	if (doc.IsObject())
	{
		std::string accountName = WebSocketManager::getInstance()->getAccountName();
		std::string name = doc["AccountName"].GetString();
		int globalID = doc["GlobalID"].GetInt();
		int sporeCount = doc["SporeCount"].GetInt();

		if (accountName == name)
		{
			_player->spitSpore(_map, _sporeMap, globalID);
			for (int i = 0; i < sporeCount; i++)
			{
				_vecSporeNeedUpdate.push_back(globalID + i);
			}

		}
		else
		{
			auto rival = _rival.at(name);
			rival->spitSpore(_map, _sporeMap, globalID);
		}

	}
}

void GameLayer::synPlayerMove()
{
	std::string accountName = WebSocketManager::getInstance()->getAccountName();
	Vec2 v = _player->getVec();

	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType & allocator = doc.GetAllocator();

	doc.AddMember("MsgType", MessageType::eMsg_MOVE, allocator);
	doc.AddMember("AccountName", rapidjson::Value(accountName.c_str(), allocator), allocator);
	//doc.AddMember("vx", rapidjson::Value(StringUtils::format("%.2f",v.x).c_str(),allocator), allocator);
	//doc.AddMember("vy", rapidjson::Value(StringUtils::format("%.2f", v.y).c_str(), allocator), allocator);
	doc.AddMember("vx", v.x, allocator);
	doc.AddMember("vy", v.y, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
	doc.Accept(write);

	std::string msg = buffer.GetString();

	WebSocketManager::getInstance()->sendMsg(msg);
}

void GameLayer::enterPlayerEvent(EventCustom * event)
{
	char * msg = (char *)event->getUserData();
	rapidjson::Document doc;
	doc.Parse<0>(msg);
	if (doc.HasParseError())
	{
		log("GetParseError %d\n", doc.GetParseError());
		return;
	}


	if (doc.IsObject())
	{
		std::string accountName = doc["PlayerInfo"]["AccountName"].GetString();
		log("Player : %s enter room", accountName.c_str());

		std::string gameName = doc["PlayerInfo"]["GameName"].GetString();
		int vestmentID = doc["PlayerInfo"]["VestmentID"].GetInt();
		int keywordID = doc["PlayerInfo"]["KeywordID"].GetInt();
		double vx = doc["PlayerInfo"]["vx"].GetDouble();
		double vy = doc["PlayerInfo"]["vy"].GetDouble();
		auto player = Player::create(gameName, vestmentID, keywordID, Vec2(vx, vy), _map);
		_map->addChild(player);
		_rival.insert(accountName, player);

		int divisionNum = doc["PlayerInfo"]["DivisionList"].Size();
		for (int j = 0; j < divisionNum; j++)
		{
			double x = doc["PlayerInfo"]["DivisionList"][j][0].GetDouble();
			double y = doc["PlayerInfo"]["DivisionList"][j][1].GetDouble();
			int score = doc["PlayerInfo"]["DivisionList"][j][2].GetInt();
			double vx = doc["PlayerInfo"]["DivisionList"][j][3].GetDouble();
			double vy = doc["PlayerInfo"]["DivisionList"][j][4].GetDouble();
			auto division = player->createDivision(Vec2(x, y), Vec2(vx, vy), score);
			_map->addChild(division, score);
		}
	}
}

void GameLayer::synPlayerConcentrate()
{
	std::string accountName = WebSocketManager::getInstance()->getAccountName();

	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType & allocator = doc.GetAllocator();

	doc.AddMember("MsgType", MessageType::eMsg_PLAYER_CONCENTRATE, allocator);
	doc.AddMember("AccountName", rapidjson::Value(accountName.c_str(), allocator), allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
	doc.Accept(write);

	std::string msg = buffer.GetString();
	WebSocketManager::getInstance()->sendMsg(msg);
}

void GameLayer::playerConcentrateEvent(EventCustom * event)
{
	char * msg = (char *)event->getUserData();
	rapidjson::Document doc;
	doc.Parse<0>(msg);
	if (doc.HasParseError())
	{
		log("GetParseError %d\n", doc.GetParseError());
		return;
	}

	if (doc.IsObject())
	{
		std::string accountName = doc["AccountName"].GetString();
		auto rival = _rival.at(accountName);
		if (rival != NULL)
		{
			rival->concentrate();
		}
	}
}

void GameLayer::updatePlayerEvent(EventCustom * event)
{
	char * msg = (char *)event->getUserData();
	rapidjson::Document doc;
	doc.Parse<0>(msg);
	if (doc.HasParseError())
	{
		log("GetParseError %d\n", doc.GetParseError());
		return;
	}

	if (doc.IsObject())
	{
		std::string accountName = doc["AccountName"].GetString();
		auto rival = _rival.at(accountName);
		if (rival != NULL)
		{
			int oldSize = rival->getDivisionNum();
			int newSize = doc["DivisionList"].Size();
			double vx = doc["vx"].GetDouble();
			double vy = doc["vy"].GetDouble();
			rival->setVec(Vec2(vx, vy));

			if (oldSize != newSize)
			{
				rival->clearDivisionList();
				for (int i = 0; i < newSize; i++)
				{
					double x = doc["DivisionList"][i][0].GetDouble();
					double y = doc["DivisionList"][i][1].GetDouble();
					int score = doc["DivisionList"][i][2].GetInt();
					auto division = rival->createDivision(Vec2(x, y), Vec2(0, 0), score);
					_map->addChild(division, score);
				}

			}
			else
			{
				Vector<PlayerDivision *> divisionList = rival->getDivisionList();
				int i = 0;
				for (auto division : divisionList)
				{
					double x = doc["DivisionList"][i][0].GetDouble();
					double y = doc["DivisionList"][i][1].GetDouble();
					int score = doc["DivisionList"][i][2].GetInt();
					if (division != NULL)
					{
						division->setPosition(Vec2(x, y));
						division->setScore(score);

					}
					i++;
				}
			}

		}
	}
}
*/
void GameLayer::sendTimeChange(float dt)
{
	_timeCount -= dt;
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("StartCountTime", &_timeCount);
}