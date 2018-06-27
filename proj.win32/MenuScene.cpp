#include "AppDelegate.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include  "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "CsvUtils.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//加载音乐
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("BGM.mp3");
	//设置默认音量
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加大厅背景
	auto backgroundM = Sprite::create("menu_background.jpg");
	backgroundM->setPosition((Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)));
	this->addChild(backgroundM, 0);
	backgroundM->setScale(0.34, 0.34);
	
	//开始游戏按钮
	MenuItemImage *startMenuItem = MenuItemImage::create(
		"menu_start_btn.png",
		"menu_start_btn.png",
		CC_CALLBACK_1(MenuScene::menuStartCallback, this)
	);
	startMenuItem->setScale(0.7, 0.7);
	startMenuItem->setPosition(640, 280);
	
	//设置按钮
	MenuItemImage *settingMenuItem = MenuItemImage::create(
		"setting_btn.png",
		"setting_btn.png",
		CC_CALLBACK_1(MenuScene::menuSettingCallback, this)
	);
	settingMenuItem->setScale(0.5, 0.5);
	settingMenuItem->setPosition(640, 150);

	auto menu = Menu::create(startMenuItem, settingMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	auto audio = SimpleAudioEngine::getInstance();

	//设置背景音乐播放
	audio->playBackgroundMusic("BGM.mp3", true);

	return true;
}


void MenuScene::menuStartCallback(Ref* pSender) 
{
	Director::getInstance()->pushScene(TransitionFade::create(1.0f, GameScene::createScene()));
}

void MenuScene::menuSettingCallback(Ref* pSender)
{
	Director::getInstance()->pushScene(TransitionFade::create(1.0f, SettingScene::createScene()));
}

void MenuScene::menuResetNameCallback(Ref * pSender)
{
	int id = rand() % 7;
	std::string name = CsvUtils::getInstance()->getMapData(id, 1, "name.csv");
	gameName->setString(name);
}