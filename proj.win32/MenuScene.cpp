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

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MenuSceneScene.cpp\n");
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
	auto backgroundM = Sprite::create("menu_background.png");
	backgroundM->setPosition((Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)));
	this->addChild(backgroundM, 0);
	

	MenuItemImage *startMenuItem = MenuItemImage::create(
		"menu_start_btn.png",
		"menu_start_btn.png",
		CC_CALLBACK_1(MenuScene::menuStartCallback, this)
	);

	startMenuItem->setPosition(383, 220);

	MenuItemImage *settingMenuItem = MenuItemImage::create(
		"Setting/setting_game_gameSetting_btn0.png",
		"Setting/setting_game_gameSetting_btn1.png",
		CC_CALLBACK_1(MenuScene::menuSettingCallback, this)
	);

	settingMenuItem->setPosition(383, 150);

	auto resetNameItem = MenuItemImage::create(
		"menu_reset.png",
		"menu_reset.png",
		CC_CALLBACK_1(MenuScene::menuResetNameCallback, this)
	);

	resetNameItem->setPosition(498, 287);

	auto playerItem = MenuItemImage::create(
		"menu_player_btn.png",
		"menu_player_btn.png",
		CC_CALLBACK_1(MenuScene::menuPlayerCallback, this)
	);
	
	playerItem->setPosition(52, 412);

	auto menu = Menu::create(startMenuItem, settingMenuItem, resetNameItem, playerItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	auto label1 = Sprite::create("menu_label1.png");
	label1->setPosition(288, 318);
	this->addChild(label1, 3);

	auto gameNameSprite = Sprite::create("menu_input_btn.png");
	gameNameSprite->setPosition(383, 287);
	this->addChild(gameNameSprite, 1);

	int id = rand() % 31 + 1;
	std::string name = CsvUtils::getInstance()->getMapData(id, 1, "name.csv");

    //创建TextField组件，并设置相关参数
	gameName = TextField::create("", "fonts/HKYuanMini", 22);
	gameName->ignoreContentAdaptWithSize(false);
	gameName->setContentSize(Size(240, 30));
	gameName->setMaxLength(12);
	gameName->setMaxLengthEnabled(true);
	gameName->setString(name);
	gameName->setTextHorizontalAlignment(TextHAlignment::LEFT);
	gameName->setTextVerticalAlignment(TextVAlignment::CENTER);
	gameName->setPosition(Vec2(368, 286));

	gameName->addEventListener(CC_CALLBACK_2(MenuScene::gameNameEvent, this));
	this->addChild(gameName, 2);

	auto audio = SimpleAudioEngine::getInstance();

	//设置背景音乐播放
	audio->playBackgroundMusic("BGM.mp3", true);



	return true;
}


void MenuScene::menuStartCallback(Ref* pSender) 
{
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void MenuScene::menuSettingCallback(Ref* pSender)
{
	auto scene = SettingScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void MenuScene::gameNameEvent(Ref * pSender, TextField::EventType type)
{

}

void MenuScene::menuPlayerCallback(Ref * pSender)
{

}

void MenuScene::menuResetNameCallback(Ref * pSender)
{
	int id = rand() % 7;
	std::string name = CsvUtils::getInstance()->getMapData(id, 1, "name.csv");
	gameName->setString(name);
}