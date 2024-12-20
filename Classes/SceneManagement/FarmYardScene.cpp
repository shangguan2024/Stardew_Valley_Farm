#include "FarmYardScene.h"
#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"
#include "Map/FarmYardMap.h"

USING_NS_CC;


Scene* FarmYardScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FarmYardScene::create();
	scene->addChild(layer);
	return scene;
}

void FarmYardScene::initConstants()
{
	tileMap = new FarmYardMap();
}
