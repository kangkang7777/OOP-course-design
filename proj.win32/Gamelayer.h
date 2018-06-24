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

	//���̲���
	void onKeyPressed(EventKeyboard::KeyCode KEY_LEFT_ARROW, cocos2d::Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	
	//touch event
	
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	
	
	//��ʼ��
	void initDataDefault();
	void initRival();
	void initPlayer();
	void initFoods();
	void initPrick();

	virtual void update(float dt);		//ÿ֡����
	void updateView();		//������Ϸ��ͼ
	void updateFoods();		//����ʳ��
	void updateRival();		//���¶���
	void updatePrick();		//�����̴�

	void updaterivalmove(float dt);
	void updateplayermove_key(Player *player);      //����player���ƶ�
	void updateplayermove_touch(Player *player);    
	void updateonExit();

	void startAddPrick(float dt);
	void addPrick(float dt);
	void collidePrick(Player * player);     //��������ײ
	void collideFoods(Player * player);		//��ʳ�����ײ���
	void collideRival();			       //����˵���ײ���

	void scoreRank(float dt);                     //����
	void randomResetFoods(float dt);            //�������ʳ��
	void resetFoods(Node * node);		//����ʳ��
	void resetPlayer();
	//void sendTimeChange(float dt);
	void timeCountDown(float dt);

private:
	//���Դ��水�µļ�
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	Node * _map;				//��ͼ
	Player * _player;			//���
	Map<std::string, Player *> _rival;		//�����б�
	Vector<Foods *> _food;			//ʳ��
	Vector<Prick *> _prick;         //�̴�
	float _mapScale;			//��ͼ��������
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