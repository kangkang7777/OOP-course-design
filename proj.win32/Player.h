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
		NORMAL, //正常状态
		DIVIDE,  //分身状态
		CONCENTRATE  //主动中合状态
	};

	static Player * create(Vec2  position, Node * map);
	bool init(Vec2  position, Node * map);

	static Player * create(Vec2  position, std::string & name, int vestmentID, int keywordID, Node * map);
	bool init(Vec2  position, std::string & name, int vestmentID, int keywordID, Node * map);

	static Player * create(std::string & name, int vestmentID, int keywordID, Vec2 velocity, Node * map);
	bool init(std::string & name, int vestmentID, int keywordID, Vec2 velocity, Node * map);

	virtual void onExit();

	Division * createDivision(Vec2 position, Vec2 velocity, int score);

	void dividePlayer();		//分身

	bool collideFoods(Foods * food);		//与食物的碰撞检测
	//bool collideSpore(Spore * spore);		//与孢子的碰撞检测
	bool collidePrick(Prick *prick);		//与刺球的碰撞检测
	bool collideRival(Player *rival);		//与对手的碰撞检测
	int collideDivision(Division * division);		//与对手分身的碰撞

	void updateDivision();		//玩家信息更新
	void resetPlayer();			//玩家复活

	void divideFinish();		//分身结束回调
	void concentrate();			//玩家中合
	void setConcentrate();		//设置中合状态
	void collidePrickFinish();	//碰到刺回调

	void setVec(Vec2 v);	//设置速度
	Vec2 getVec();			//获取速度

	Rect getPlayerRect();		//获取玩家包围盒
	void setCombine(float dt);
	int getDivisionNum();		//获取当前分身数量
	float getTotalWeight();     //总体重
	std::string getPlayerName();
	int getTotalScore();        //总分数
	Vector<Division *> & getDivisionList();
	void clearDivisionList();
private:
	Vector<Division *> _divisionList;		//玩家分身列表
	int _divisionNum;							//分身数量

	Node * _map;			//layer指针
	std::string _playerName;		//玩家名
	int _vestmentID;		//圣衣id
	int _keywordID;			//关键字id

	Vec2 _vector;			//位移
	int _color;			//颜色,没有关键字时可用

	State _state;		//玩家状态
	bool _combineEnable; //分身是否可以合体
};

#endif