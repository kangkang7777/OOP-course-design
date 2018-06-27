#ifndef _GameScene_H_
#define _GameScene_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Gamelayer.h"
#include "GamePause.h"
USING_NS_CC;

using namespace ui;

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	
};
#endif