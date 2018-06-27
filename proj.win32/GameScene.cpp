

#include "GameScene.h"
Scene* GameScene::createScene()
{
	auto scene = GameScene::create();
	auto gameLayer = GameLayer::create();
	scene->addChild(gameLayer, 1);

	return scene;
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
	//���ز˵����棬��ջ
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f,GameScene::createScene()));

}
