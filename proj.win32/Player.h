#ifndef  _Player_
#define  _Player_

#include "cocos2d.h"

USING_NS_CC;

class Prick;
class Division;
class Foods;
class Spore;

class Player :public Node
{
public:
	Player();
	~Player();
	enum class State
	{
		NORMAL, //����״̬
		DIVIDE,  //����״̬
		CONCENTRATE  //�����к�״̬
	};

	static Player * create(Vec2  position, Node * map);
	bool init(Vec2  position, Node * map);

	static Player * create(Vec2  position, std::string & name, int vestmentID, int keywordID, Node * map);
	bool init(Vec2  position, std::string & name, int vestmentID, int keywordID, Node * map);

	static Player * create(std::string & name, int vestmentID, int keywordID, Vec2 velocity, Node * map);
	bool init(std::string & name, int vestmentID, int keywordID, Vec2 velocity, Node * map);

	virtual void onExit();

	Division * createDivision(Vec2 position, Vec2 velocity, int score);

	void dividePlayer();		//����

	bool collideFoods(Foods * food);		//��ʳ�����ײ���
	//bool collideSpore(Spore * spore);		//�����ӵ���ײ���
	bool collidePrick(Prick *prick);		//��������ײ���
	bool collideRival(Player *rival);		//����ֵ���ײ���
	int collideDivision(Division * division);		//����ַ������ײ

	void updateDivision();		//�����Ϣ����
	void resetPlayer();			//��Ҹ���

	void divideFinish();		//��������ص�
	void concentrate();			//����к�
	void setConcentrate();		//�����к�״̬
	void collidePrickFinish();	//�����̻ص�

	void setVec(Vec2 v);	//�����ٶ�
	Vec2 getVec();			//��ȡ�ٶ�

	Rect getPlayerRect();		//��ȡ��Ұ�Χ��
	void setCombine(float dt);
	int getDivisionNum();		//��ȡ��ǰ��������
	float getTotalWeight();     //������
	std::string getPlayerName();
	int getTotalScore();        //�ܷ���
	Vector<Division *> & getDivisionList();
	void clearDivisionList();
private:
	Vector<Division *> _divisionList;		//��ҷ����б�
	int _divisionNum;							//��������

	Node * _map;			//layerָ��
	std::string _playerName;		//�����
	int _vestmentID;		//ʥ��id
	int _keywordID;			//�ؼ���id

	Vec2 _vector;			//λ��
	int _color;			//��ɫ,û�йؼ���ʱ����

	State _state;		//���״̬
	bool _combineEnable; //�����Ƿ���Ժ���
};

#endif