#ifndef __SettingScene_H__
#define __SettingScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "iostream"
#include "MenuScene.h"
#include "Function.h"
USING_NS_CC;
using namespace cocos2d::ui;

class SettingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void soundCallback(cocos2d::Ref* pSender);  //音效开关按钮回调
	void settingReturnCallback(cocos2d::Ref* pSender);  //返回按钮回调
	void SliderCallBack(Ref *pSender, Slider::EventType type);  //滑动条控件回调
	void playCallback(Ref* pSender)
	{
		MenuItemToggle* playToggleMenuItem = (MenuItemToggle *)pSender;
		if (playToggleMenuItem->getSelectedIndex() == 0)
		{
			
		}
		else if (playToggleMenuItem->getSelectedIndex() == 1)
		{
		
		}
	}
	// implement the "static create()" method manually
	CREATE_FUNC(SettingScene);

};

#endif