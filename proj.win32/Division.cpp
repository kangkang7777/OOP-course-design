#include "Division.h"
#include "macro.h"
#include "Foods.h"
#include "Prick.h"
#include "Spore.h"

Division::Division()
{

}

Division::~Division()
{

}

Division * Division::create(const std::string& filename)
{
	Division * playerDivision = new Division();
	if (playerDivision && playerDivision->init(filename))
	{
		playerDivision->autorelease();
		return playerDivision;
	}
	CC_SAFE_DELETE(playerDivision);
	return nullptr;
}

bool Division::init(const std::string& filename)
{
	if (!Entity::initWithFile(filename))
	{
		return false;
	}

	return true;
}

Division * Division::create(const std::string &name, int vestmentID, int keywordID, int score)
{
	Division * playerDivision = new Division();
	if (playerDivision && playerDivision->init(name, vestmentID, keywordID, score))
	{
		playerDivision->autorelease();
		return playerDivision;
	}
	CC_SAFE_DELETE(playerDivision);
	return nullptr;
}

bool Division::init(const std::string &name, int vestmentID, int keywordID, int score)
{
	_name = name;
	_vestmentID = vestmentID;
	_keywordID = keywordID;

	if (!Entity::initWithFile(StringUtils::format("public/keyword_%d.png", _keywordID)))
	{
		return false;
	}

	_score = score;
	calculateData();

	return true;
}

bool Division::collideFoods(Foods * food)
{
	Vec2 position = this->getPosition();
	Vec2 foodPosition = food->getPosition();
	if (foodPosition.distance(position) <= _radius)
	{
		eatFoods(food);
		return true;
	}

	return false;
}

float Division::getSpeed()
{
	return _speed;
}

void Division::eatFoods(Foods * food)
{
	_score += food->getScore();
	calculateData();
}

void Division::eatRival(int score)
{
	_score += score;
	calculateData();
}

void Division::eatPrick(int score)
{
	_score = score;
	calculateData();
}

void Division::scaleSprite()
{
	if (_score >= PLAYER_MIN_SHOW_VESTMENT_SCORE && !_showVestment)
	{
		_showVestment = true;
		std::string path = StringUtils::format("public/keyword_%d.png", _vestmentID);
		this->setTexture(path);
	}
	else if (_score<200 && _showVestment)
	{
		_showVestment = false;
		std::string path = StringUtils::format("public/keyword_%d.png", _keywordID);
		this->setTexture(path);
	}

	Size size = this->getContentSize();
	float scale = float(_radius * 2) / size.width;

	this->setScale(scale);
}
/*
void Division::spitSpore()
{
	_score -= SPORE_SCORE;
	calculateData();
}

bool Division::collideSpore(Spore * spore)
{
	if (_score<PLAYER_MIN_EAT_SPORE_SCORE)
	{
		return false;
	}

	Vec2 position = this->getPosition();
	Vec2 sporePosition = spore->getPosition();
	if (position.distance(sporePosition) <= _radius)
	{
		eatSpore(spore);
		return true;
	}
	return false;
}

void Division::eatSpore(Spore * spore)
{
	_score += spore->getScore();
	calculateData();
}
*/
void Division::divide()
{
	_score /= 2;
	calculateData();

}

void Division::addWeight(float w)
{
	_weight += w;

}

void Division::setWeight(float w)
{
	_weight = w;

}

float Division::getWeight()
{
	return _weight;
}

void Division::setVelocity(Vec2 v)
{
	_vector = v;
}

Vec2 Division::getVec()
{
	return _vector;
}

bool Division::collidePrick(Prick * prick)
{
	float prickScore = prick->getScore();

	if (_score>prickScore*MIN_EAT_MULTIPLE)
	{
		Vec2 prickPosition = prick->getPosition();
		Vec2 divisionPostion = this->getPosition();
		float distance = prickPosition.distance(divisionPostion);
		if (distance <= abs(_radius - prick->getRadius()))
		{
			return true;
		}
	}
	return false;
}

void Division::setVestmentID(int id)
{
	_vestmentID = id;
}

void Division::setPlayerName(const std::string name)
{
	_nameLabel = Label::createWithTTF(name.c_str(), "fonts/STSONG.TTF", 22);
	Size size = this->getContentSize();
	_nameLabel->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(_nameLabel);
}

void Division::calculateData()
{
	_radius = sqrt(_score * PLAYER_INITIAL_RADIUS * PLAYER_INITIAL_RADIUS / PLAYER_INITIAL_SCORE);
	_speed = (PLAYER_INITIAL_RADIUS / _radius) * (PLAYER_INITIAL_SPEED - PLAYER_MIN_SPEED) + PLAYER_MIN_SPEED;

	this->setLocalZOrder(_score);
	scaleSprite();
}

void Division::setScore(int score)
{
	_score = score;
	calculateData();
}

void Division::setPrePosition(const Vec2 & position)
{
	_prePosition = position;
}

Vec2 Division::getPrePosition()
{
	return _prePosition;
}