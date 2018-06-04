#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//add the background
	void background();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	//add the player
	//void Player();
	//add mouse listener
	
	// implement the "static create()" method manually
	void updatePoint(float dt);

	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchMoved(Touch* touch, Event* event);
	CREATE_FUNC(GameScene);

private:
	Vec2 startPoint;
	//Sprite* player;
	
};