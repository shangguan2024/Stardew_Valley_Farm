#include "FarmYard.h"

#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"

USING_NS_CC;


Scene* FarmYard::createScene()
{
	auto scene = Scene::create();
	auto layer = FarmYard::create();
	scene->addChild(layer);
	return scene;
}

void FarmYard::initConstants()
{
	mapName = MapName::FarmYard;
	tileMapPath = Texture::Beach;
}
