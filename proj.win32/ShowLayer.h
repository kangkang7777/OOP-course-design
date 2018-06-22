#ifndef _ShowLayer_H_
#define _ShowLayer_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

class ShowLayer : public Layer {
public:
	ShowLayer();
	~ShowLayer();

	virtual bool init();

	CREATE_FUNC(ShowLayer);
	/*
	virtual void onExit();

	void updateTime(EventCustom * event);
	void updateScore(EventCustom * event);
	void updateRank(EventCustom * event);

	void menuRankCallback(Ref * pSender);
	*/
private:
	/*
	Label * _timeLabel;
	Label * _scoreLabe;
	
	Vector<Label *> _rankList;
	Sprite * _rankSprite;
	Scale9Sprite * _rankBk1;
	Scale9Sprite * _rankBk2;
	Scale9Sprite * _rankBk3;
	*/

	int _timeTotal;
};


#endif