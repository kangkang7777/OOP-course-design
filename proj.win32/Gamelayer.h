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
#include "Prick.h"
#include "Division.h"
#include "GameScene.h"
#include "SettingScene.h"

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
	
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	
	
	//初始化
	void initDataDefault();
	void initRival();
	void initPlayer();
	void initFoods();
	void initPrick();

	virtual void update(float dt);		//每帧更新
	void updateView();		//更新游戏视图
	void updateFoods();		//更新食物
	void updateRival();		//更新对手
	void updatePrick();		//更新绿刺

	void updaterivalmove(float dt);
	void updateplayermove_key(Player *player);      //所有player的移动
	void updateplayermove_touch(Player *player);    
	void updateonExit();

	void startAddPrick(float dt);
	void addPrick(float dt);
	void collidePrick(Player * player);     //与刺球的碰撞
	void collideFoods(Player * player);		//与食物的碰撞检测
	void collideRival();			       //与敌人的碰撞检测

	void scoreRank(float dt);                     //分数
	void randomResetFoods(float dt);            //随机重置食物
	void resetFoods(Node * node);		//重置食物
	void resetPlayer();
	//void sendTimeChange(float dt);
	void timeCountDown(float dt);

private:
	//用以储存按下的键
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	Node * _map;				//地图
	Player * _player;			//玩家
	Map<std::string, Player *> _rival;		//对手列表
	Vector<Foods *> _food;			//食物
	Vector<Prick *> _prick;         //绿刺
	float _mapScale;			//地图缩放因子
	Node * _Njoystick;
	Node * _scoreBoard;
	Sprite * _joystick;
	Vec2 _touchEventVec;
	Label* label1;
	Label* label2;
	Label* label3;
	Label* labelMy;
	std::string name[20] = { "Sydi","Soo","Ali","Stern","Alica","Owen","Fans","Quene","Meimen","Prik","Greg","Laura","Edward","Barbara"
		,"Yang","Lynn","Pete","Llyod" };

	Label * _timeLabel;
	int maxTime = 300;
	Node * _timeBoard;
	Sprite * _joySteer;
};

#endif