<<<<<<< Updated upstream
#include "FarmYardScene.h"

USING_NS_CC;

Scene* FarmYardScene::createScene() 
{
	return FarmYardScene::create();
}

bool FarmYardScene::init() 
{
	if (!Scene::init())
	{
		return false;
	}

	MapBg* farm_map = FarmYardBackground::create();
	addChild(farm_map);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	PlayerPosition* player = PlayerPosition::create(visibleSize.width / 2, visibleSize.height / 2);

	addChild(player);
	return true;
}

MapBg* FarmYardBackground::createMap() 
{
	return MapBg::create();
}

bool FarmYardBackground::init() 
{
	if (!MapBg::init()) 
	{
		return false;
	}

#if 0
	auto farm_map = TMXTiledMap::create(files_name);
	if (!farm_map) 
	{
		CCLOG("Failed to load TMX file named ");
	}
	farm_map->setPosition(Vec2(0, 0));
	this->addChild(farm_map, 0, 100);
#endif
	MapBg::LoadTMXMap(files_name);

	return true;
=======
/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.cpp
 * File Function: FarmYardScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/4
 ****************************************************************/

#include "FarmYardScene.h"
#include "../Player/Player.h"

USING_NS_CC;

Scene* FarmYardScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FarmYardScene::create();
	scene->addChild(layer);
	return scene;
}

bool FarmYardScene::init()
{
	if (!Scene::init()) {
		return false;
	}



    // 启用帧更新
    this->scheduleUpdate();

    return true;
}

void FarmYardScene::update(float delta)
{

>>>>>>> Stashed changes
}
