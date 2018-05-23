
#include "cocos2d.h"
#include<iostream>
class MenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// another selector callback
	void gameStartCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
};