#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "math.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// trigger when moving touch
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	//
	void onKeyPressed(EventKeyboard::KeyCode KEY_LEFT_ARROW, cocos2d::Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void keyPressedDuration();
	void borderControl(float fDelta);
	//
	void update(float delta);

	CREATE_FUNC(GameScene);
private:
	
	CCSprite *player ;
	Point _start_center_Point;
	Point _movePoint;
	Sprite* steer;
	//player的位置
	float var_x, var_y;
	//用以储存按下的键
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};