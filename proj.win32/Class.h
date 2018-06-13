#ifndef  _Class_
#define  _Class_

#include "Entity.h"


class Player :public Entity
{
public:
	Player();
	~Player();
	static Player * create(const std::string& filename);
	bool init(const std::string& filename);
	void setVector(float x, float y)
	{
		var_x = x;
		var_y = y;
	}
	float var_x, var_y;//player要移动的向量
	float speed = 1;
};

#endif