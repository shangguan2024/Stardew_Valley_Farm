#include "Beach.h"

#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"

USING_NS_CC;


Scene* Beach::createScene()
{
	auto scene = Scene::create();
	auto layer = Beach::create();
	scene->addChild(layer);
	return scene;
}

void Beach::initConstants()
{
	sceneName = "Beach";
	tileMapPath = Texture::Beach;
}
