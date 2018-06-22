#include "ShowLayer.h"
#include "macro.h"
#include "Player.h"


ShowLayer::ShowLayer()
{

}

ShowLayer::~ShowLayer()
{

}

bool  ShowLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//Éú³É±³¾°
	auto map = Sprite::create("background.jpg");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(0, 0);
	this->addChild(map, 0);

	_timeTotal = GAME_TOTAL_TIME;

	return true;
}
