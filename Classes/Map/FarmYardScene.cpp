/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.cpp
 * File Function: FarmYardScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/5
 ****************************************************************/
#include "FarmYardScene.h"
#include "../Player/Player.h"

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
	auto FarmYard = TMXTiledMap::create("Maps/FarmYardScene.tmx");
	if (!FarmYard) {
		CCLOG("Failed to load tile map");
		return false;
	}

	this->addChild(FarmYard, 0, "FarmYard");

	auto mapSize = FarmYard->getMapSize();
	auto tileSize = FarmYard->getTileSize();
	auto mapCenter = Vec2(mapSize.width * tileSize.width / 2, mapSize.height * tileSize.height / 2);

	auto objectGroup = FarmYard->getObjectGroup("Event");
	if (!objectGroup) {
		CCLOG("Failed to load object layer: Event");
		return false;
	}

	auto spawnPoint = objectGroup->getObject("SpawnPoint");
	if (spawnPoint.empty()) {
		CCLOG("SpawnPoint not found in Event layer.");
		return false;
	}

	// 提取出生点的 x 和 y 坐标
	float spawnX = spawnPoint["x"].asFloat();
	float spawnY = spawnPoint["y"].asFloat();
	CCLOG("Spawn point coordinates: (%f, %f)", spawnX, spawnY);

	FarmYard->setPosition(0,0);

	auto player = Player::getInstance();

	player->setPosition(100, 100);

	this->addChild(player);

	this->scheduleUpdate();

	return true;
}

void FarmYardScene::update(float delta)
{
	Player* player = Player::getInstance();

	Vec2 _direction = player->getDirection();
	float _speed = player->getSpeed();
	Vec2 currentPosition = player->getPosition();

	Vec2 newPosition = currentPosition + _direction * _speed * delta;

	player->setPosition(newPosition);
}