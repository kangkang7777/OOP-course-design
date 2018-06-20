#ifndef _GameLayer_H_
#define _GameLayer_H_

#include "cocos2d.h"
#include "macro.h"
#include "ui\CocosGUI.h"
#include "GameLayer.h"
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

	//���̲���
	void onKeyPressed(EventKeyboard::KeyCode KEY_LEFT_ARROW, cocos2d::Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	
	
	//void initData();			//��ʼ����ͼ����
	//void initRival(rapidjson::Value &value);		//��ʼ������
	//void initPlayer(rapidjson::Value &value);		//��ʼ�����
	//void initFoods(int seed);						//��ʼ��ʳ��
	//void initSpore(rapidjson::Value &value);		//��ʼ������
	//void initPrick(rapidjson::Value &value);		//��ʼ���̴�

	//��ʼ��
	void initDataDefault();
	void initRival();
	void initPlayer();
	void initFoods();
	void initPrick();

	virtual void update(float dt);		//ÿ֡����
	void updateView();		//������Ϸ��ͼ
	void updateFoods();		//����ʳ��
	void updateSpore();		//��������
	void updatePrick();		//�����̴�
	void updateRival();		//���¶���
	void updateRank(float dt);		//�������а���Ϣ
	void updateScore(float dt);		//���·���
	void updateplayermove(Player *player);      //����player���ƶ�

	void startAddPrick(float dt);
	void addPrick(float dt);

	void collideFoods(Player * player);		//��ʳ�����ײ���
	void collide();			//��ײ���

	void resetFoods(Node * node);		//����ʳ��
	void resetPlayer();
	/*
	void spitSpore();		//�����Ӳ���
	void dividePlayer();		//�������

	void synPlayerMove();		//ͬ������ƶ�
	void synPlayerInfo();		//ͬ�������Ϣ
	void synSporeInfo();		//ͬ������
	void synPlayerConcentrate();		//ͬ������кϲ���

									//���������������Ϣ
									
	void playerMoveEvent(EventCustom * event);
	void playerDivideEvent(EventCustom * event);
	void spitSporeResultEvent(EventCustom * event);
	void addPrickEvent(EventCustom * event);
	void enterPlayerEvent(EventCustom * event);
	void playerConcentrateEvent(EventCustom * event);
	void updatePlayerEvent(EventCustom * event);
	*/
	void sendTimeChange(float dt);
private:

	//���Դ��水�µļ�
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	Node * _map;				//��ͼ
	Player * _player;			//���
	Map<std::string, Player *> _rival;		//�����б�
	Vector<Foods *> _food;			//ʳ��
	Map<int, Prick *> _prickMap;			//�̴�
	Map<int, Spore *> _sporeMap;			//����
	std::vector<int> _vecSporeNeedUpdate;			//��Ҫ���µ�����
	float _mapScale;			//��ͼ��������
	float _timeCount;
	int _mode;			//��Ϸģʽ
	int _roomID;		//����id
};

#endif