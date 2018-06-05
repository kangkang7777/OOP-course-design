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

	bool onTouchBegan(Touch *touch, Event *event);
	// trigger when moving touch
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	CREATE_FUNC(GameScene);

private:
	Point _start_center_Point;
	Point _movePoint;
	Sprite* steer;
};