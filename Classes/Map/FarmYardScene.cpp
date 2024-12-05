/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.cpp
 * File Function: FarmYardScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/5
 ****************************************************************/
#include "FarmYardScene.h"

USING_NS_CC;

// 创建场景
Scene* FarmYardScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FarmYardScene::create();
	scene->addChild(layer);
	return scene;
}

// 初始化场景
bool FarmYardScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// 加载瓦片地图
	auto tileMap = TMXTiledMap::create("Maps/FarmYardScene.tmx");
	if (!tileMap) {
		CCLOG("Failed to load tile map");
		return false;
	}

	auto mapSize = tileMap->getMapSize();
	auto tileSize = tileMap->getTileSize();
	auto mapCenter = Vec2(mapSize.width * tileSize.width / 2, mapSize.height * tileSize.height / 2);
	this->setPosition(mapCenter);

	this->addChild(tileMap, 0, "TileMap");

	auto objectGroup = tileMap->getObjectGroup("Event");
	if (!objectGroup) {
		CCLOG("Failed to load object layer: Event");
		return false;
	}

	auto spawnPoint = objectGroup->getObject("SpawnPoint");
	if (spawnPoint.empty()) {
		CCLOG("SpawnPoint not found in Event layer.");
		return false;
	}

	float x = spawnPoint.count("x") > 0 ? spawnPoint["x"].asFloat() : 0.0f;
	float y = spawnPoint.count("y") > 0 ? spawnPoint["y"].asFloat() : 0.0f;
	CCLOG("Spawn point at (%f, %f)", x, y);



	return true;
}

void FarmYardScene::update(float delta)
{

}