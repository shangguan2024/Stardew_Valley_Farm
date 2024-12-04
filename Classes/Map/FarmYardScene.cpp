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
	//添加场景地图
	auto visibleSize = Director::getInstance()->getVisibleSize();
	PlayerPosition* player = PlayerPosition::create(visibleSize.width / 2, visibleSize.height / 2);
	//此处仅为放置player的位置
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
	//添加TMX地图
	return true;
}
