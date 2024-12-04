#include "BackgroundTiledMap.h"

USING_NS_CC;

MapBg* MapBg::create()
{
	MapBg* tbg = new MapBg();
	if (tbg && tbg->init())
	{
		tbg->autorelease();
		return tbg;
	}
	else
	{
		CC_SAFE_DELETE(tbg);
	}
	return nullptr;
}

bool MapBg::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

bool MapBg::LoadTMXMap(std::string map_name)
{
	auto map = TMXTiledMap::create(map_name);
	if (!map)
	{
		CCLOG("MapBg: Failed to load TMX file");
		return false;
	}
	map->setPosition(Vec2(0, 0));

	this->addChild(map, 0, 100);
	return true;
}