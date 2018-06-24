#ifndef __SettingScene_CPP__
#define __SettingScene_CPP__


#include "SettingScene.h"



using namespace cocos2d::ui;
using namespace CocosDenshion;

Scene* SettingScene::createScene()
{
	return SettingScene::create();
}

bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加设置界面背景
	auto backgroundS = Sprite::create("setting_background.png");
	backgroundS->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backgroundS);
	backgroundS->setScale(0.34, 0.34);

	//音效开关按钮
	auto soundOnMenuItem = MenuItemImage::create(
		"Setting/setting_game_on.png",
		"Setting/setting_game_on.png"
	);
	auto soundOffMenuItem = MenuItemImage::create(
		"Setting/setting_game_off.png", 
		"Setting/setting_game_off.png"
	);

	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingScene::soundCallback, this),
		soundOnMenuItem,
		soundOffMenuItem,
		NULL
	);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Point(600, 177)));

	auto label_1 = Label::createWithTTF("S  O  U  N  D", "fonts/Marker Felt.ttf", 30);
	label_1->setPosition(Director::getInstance()->convertToGL(Point(237, 180)));
	this->addChild(label_1, 1);

	label_1->enableOutline(Color4B(173, 225, 47, 255), 4);

	auto label_2 = Label::createWithTTF("S O U N D  V O L U M E", "fonts/Marker Felt.ttf", 30);
	label_2->setPosition(Director::getInstance()->convertToGL(Point(300, 240)));
	this->addChild(label_2, 1);

	label_2->enableOutline(Color4B(173, 225, 47, 255), 4);

	//鼠标操作开关按钮
	auto keyMenuItem = MenuItemImage::create(
		"Setting/setting_game_off.png",
		"Setting/setting_game_off.png"
	);

	auto mouseMenuItem = MenuItemImage::create(
		"Setting/setting_game_on.png",
		"Setting/setting_game_on.png"
	);

	auto playToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingScene::playCallback, this),
		keyMenuItem,
		mouseMenuItem,
		NULL
	);
	playToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Point(600, 358)));

	auto label_3 = Label::createWithTTF("PLAY  BY  MOUSE", "fonts/Marker Felt.ttf", 30);
	label_3->setPosition(Director::getInstance()->convertToGL(Point(273, 358)));
	this->addChild(label_3, 1);

	label_3->enableOutline(Color4B(173, 225, 47, 255), 4);


	//创建滑动条
	auto slider = Slider::create();
	slider->loadBarTexture("Setting/setting_game_sliderTrack_0.png");
	slider->loadSlidBallTextures(
		"Setting/setting_game_sliderThumb.png", 
		"Setting/setting_game_sliderThumb.png", 
		"Setting/setting_game_sliderThumb.png"
	);
	slider->loadProgressBarTexture("Setting/setting_game_sliderTrack_1.jpg");

	slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			std::cout << "slider moved" << std::endl;
			break;
		default:
			break;
		}
	});

	slider->setPosition(Director::getInstance()->convertToGL(Point(400, 300)));
	slider->addEventListener(CC_CALLBACK_2(SettingScene::SliderCallBack, this));
	this->addChild(slider);

	//返回按钮
	MenuItemImage *returnItem = MenuItemImage::create(
		"Setting/return_btn0.png",
		"Setting/return_btn1.png",
		CC_CALLBACK_1(SettingScene::settingReturnCallback, this)
	);
	float x = origin.x + returnItem->getContentSize().width / 2;
	float y = origin.y + visibleSize.height - returnItem->getContentSize().height / 2;
	returnItem->setPosition(Vec2(x, y));

	auto setting = Menu::create(soundToggleMenuItem, playToggleMenuItem, returnItem, NULL);
	setting->setPosition(Vec2::ZERO);
	this->addChild(setting);

	return true;
}


void SettingScene::soundCallback(Ref* pSender)
{
	MenuItemToggle* soundToggleMenuItem = (MenuItemToggle *)pSender;
	if (soundToggleMenuItem->getSelectedIndex() == 0) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM.mp3", true);
		UserDefault::getInstance()->setBoolForKey("musicOff", false);
	}
	else if (soundToggleMenuItem->getSelectedIndex() == 1) {
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		UserDefault::getInstance()->setBoolForKey("musicOff", true);
	}

}



void SettingScene::settingReturnCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void SettingScene::SliderCallBack(Ref *pSender, Slider::EventType type) 
{
	auto item = (Slider*)(pSender);
	log("%i", item->getPercent());
	if (item->getPercent() == 100) 
	{
		item->setEnabled(false);
	}
	else 
	{
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(item->getPercent() / 100.0f);
	}
}


#endif