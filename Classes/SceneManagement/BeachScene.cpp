#include "BeachScene.h"
#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"
#include "Map/BeachMap.h"

USING_NS_CC;

Scene* BeachScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BeachScene::create();
	scene->addChild(layer);
	return scene;
}

void BeachScene::initConstants()
{
	tileMap = new BeachMap();
}
