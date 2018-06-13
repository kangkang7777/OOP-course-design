#include "Class.h"

Player::Player()
{

}

Player::~Player()
{

}

Player * Player::create(const std::string& filename)
{
	Player * _player = new Player();
	if (_player && _player->init(filename))
	{
		_player->autorelease();
		return _player;
	}
	CC_SAFE_DELETE(_player);
	return nullptr;
}

bool Player::init(const std::string& filename)
{
	if (!Entity::initWithSpriteFrameName(filename))
	{
		return false;
	}

	_score = 1;
	_radius = 8;

	Size size = this->getContentSize();
	float scale = (_radius * 2) / size.width;
	this->setScale(scale);

	return true;
}
