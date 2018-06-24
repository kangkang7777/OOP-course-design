#ifndef __MenuScene_H__
#define __MenuScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class MenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuStartCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void gameNameEvent(Ref * pSender, TextField::EventType type);
	void menuPlayerCallback(Ref * pSender);
	void menuResetNameCallback(Ref * pSender);

	TextField * gameName;

	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
};

#endif
