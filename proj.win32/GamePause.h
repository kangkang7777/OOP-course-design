#ifndef __Gamepause__H__  
#define __Gamepause__H__  

#include "cocos2d.h"  
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "MenuScene.h"
USING_NS_CC;
using namespace ui;

class Gamepause : public cocos2d::Scene
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Gamepause);
	//¼ÌÐøÓÎÏ·  
	void ContinueCallback(CCObject* pSender);
	void ExitCallback(CCObject* pSender);
	void menuCallback(CCObject* pSender);
private:

};

#endif 