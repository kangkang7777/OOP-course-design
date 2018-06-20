#ifndef _Division_H_
#define _Division_H_

#include "Entity.h"

class Foods;
class Prick;
class Spore;

class Division : public Entity {
public:
	Division();
	~Division();

	static Division * create(const std::string& filename);
	bool init(const std::string& filename);

	static Division * create(const std::string &name, int vestmentID, int keywordID, int score);
	bool init(const std::string &name, const int vestmentID, int keywordID, int score);

	bool collideFoods(Foods * food);
	bool collideSpore(Spore *spore);
	bool collidePrick(Prick *prick);

	float getSpeed();
	void calculateData();

	void eatFoods(Foods * food);
	void eatSpore(Spore * spore);
	void eatRival(int score);
	void eatPrick(int score);

	virtual void setScore(int score);

	void spitSpore();
	void divide();
	void scaleSprite();
	void setVestmentID(int id);
	void setPlayerName(const std::string name);
	void addWeight(float weight);
	void setWeight(float weight);
	float getWeight();
	void setVelocity(Vec2 v);
	Vec2 getVec();

	void setPrePosition(const Vec2 & position);
	Vec2 getPrePosition();
private:
	Label * _nameLabel;
	std::string _name;
	int _vestmentID;
	int _keywordID;

	float _speed;
	float _weight;
	Vec2 _vector;

	bool _showVestment;

	Vec2 _prePosition;  //上一帧的位置
};

#endif