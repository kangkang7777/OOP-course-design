#ifndef _GameLayer_H_
#define _GameLayer_H_
#include "cocos2d.h"
#include "macro.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "Function.h"
#include "Player.h"
#include "Entity.h"
#include "Foods.h"
#include "Spore.h"
#include "Prick.h"
#include "Division.h"
#include "GameScene.h"

USING_NS_CC_EXT;
USING_NS_CC;

using namespace ui;

class Player;
class Foods;
class Spore;
class Prick;

class GameLayer : public Layer {
public:
	GameLayer();
	~GameLayer();

	virtual bool init();

	CREATE_FUNC(GameLayer);

	virtual void onExit();

	//键盘操作
	void onKeyPressed(EventKeyboard::KeyCode KEY_LEFT_ARROW, cocos2d::Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	
	//touch event
	/*
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	*/
	
	//void initData();			//初始化地图数据
	//void initRival(rapidjson::Value &value);		//初始化对手
	//void initPlayer(rapidjson::Value &value);		//初始化玩家
	//void initFoods(int seed);						//初始化食物
	//void initSpore(rapidjson::Value &value);		//初始化孢子
	//void initPrick(rapidjson::Value &value);		//初始化绿刺

	//初始化
	void initDataDefault();
	void initRival();
	void initPlayer();
	void initFoods();
	void initPrick();

	virtual void update(float dt);		//每帧更新
	void updateView();		//更新游戏视图
	void updateFoods();		//更新食物
	void updateSpore();		//更新孢子
	void updateRival();		//更新对手
	void updatePrick();		//更新绿刺
	/*
	void updateRank(float dt);		//更新排行榜信息
	void updateScore(float dt);		//更新分数
	*/
	void updateplayermove_key(Player *player);      //所有player的移动
	//void updateplayermove_touch(Player *player);      

	void startAddPrick(float dt);
	void addPrick(float dt);

	void collideFoods(Player * player);		//与食物的碰撞检测
	void collideRival();			       //与敌人的碰撞检测

	void resetFoods(Node * node);		//重置食物
	void resetPlayer();
	/*
	void spitSpore();		//吐孢子操作
	void dividePlayer();		//分身操作

	void synPlayerMove();		//同步玩家移动
	void synPlayerInfo();		//同步玩家信息
	void synSporeInfo();		//同步孢子
	void synPlayerConcentrate();		//同步玩家中合操作

									//处理服务器返回消息
									
	void playerMoveEvent(EventCustom * event);
	void playerDivideEvent(EventCustom * event);
	void spitSporeResultEvent(EventCustom * event);
	void addPrickEvent(EventCustom * event);
	void enterPlayerEvent(EventCustom * event);
	void playerConcentrateEvent(EventCustom * event);
	void updatePlayerEvent(EventCustom * event);
	*/
	//void sendTimeChange(float dt);
private:

	//用以储存按下的键
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	Node * _map;				//地图
	Player * _player;			//玩家
	Map<std::string, Player *> _rival;		//对手列表
	Vector<Foods *> _food;			//食物
	Map<int, Prick *> _prickMap;			//绿刺
	Map<int, Spore *> _sporeMap;			//孢子
	std::vector<int> _vecSporeNeedUpdate;			//需要更新的孢子
	float _mapScale;			//地图缩放因子
	//float _timeCount;
	//int _mode;			//游戏模式
	//int _roomID;		//房间id
};

#endif