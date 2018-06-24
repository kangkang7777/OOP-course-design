

#include "GameScene.h"
Scene* GameScene::createScene()
{
	auto scene = GameScene::create();
	auto gameLayer = GameLayer::create();
	scene->addChild(gameLayer, 1);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
	//返回菜单界面，出栈
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f,GameScene::createScene()));

}
