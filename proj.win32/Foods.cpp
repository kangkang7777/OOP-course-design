#include "Foods.h"
#include "macro.h"

Foods::Foods()
{

}

Foods::~Foods()
{

}

Foods * Foods::create(const std::string& filename)
{
	Foods * food = new Foods();
	if (food && food->init(filename))
	{
		food->autorelease();
		return food;
	}
	CC_SAFE_DELETE(food);
	return nullptr;
}

bool Foods::init(const std::string& filename)
{
	if (!Entity::initWithFile(filename))
	{
		return false;
	}
	_score = BEAN_SCORE;
	_radius = BEAN_RADIUS;

	Size size = this->getContentSize();
	float scale = (_radius * 2) / size.width;
	this->setScale(scale);

	return true;
}