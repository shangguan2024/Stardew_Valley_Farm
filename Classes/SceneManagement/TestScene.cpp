#include "TestScene.h"
#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"
#include "Map/TestMap.h"

USING_NS_CC;

Scene* TestScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TestScene::create();
	scene->addChild(layer);
	return scene;
}

void TestScene::initConstants()
{
	tileMap = new TestMap();
	sceneName = "Test";
}
