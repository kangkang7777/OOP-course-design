#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "Function.h"
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
	//
	void onKeyPressed(EventKeyboard::KeyCode KEY_LEFT_ARROW, cocos2d::Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void keyPressedDuration();
	void borderControl(float fDelta);
	void foodGenerate();
	//
	void update(float delta);

	CREATE_FUNC(GameScene);
private:
	
	Sprite *player ;
	//用以储存按下的键
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	int var_x, var_y;
	//食物
	std::map<int, Sprite *> foods;
};