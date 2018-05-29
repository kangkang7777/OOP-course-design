#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "cocos-ext.h"
#include<iostream>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
class MenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// another selector callback
	void MenuScene::gameStartCallback(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
};