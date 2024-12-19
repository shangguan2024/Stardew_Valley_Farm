#include "MapManager.h"
#include "GameTime/GameTime.h"

USING_NS_CC;

MapManager* MapManager::instance = nullptr;

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
}

MapManager* MapManager::getInstacne()
{
	if (!instance) {
		instance = new MapManager();
	}
	return instance;
}

std::vector<MapManager::TileData>& MapManager::getTileData(MapName mapName)
{
	return tiles[mapName];
}

// return (tileData has changed ? true : false);
bool MapManager::updateTileData(TileData& tileData)
{
	int deltaTime = GameTime::getInstance()->getTimeStamp() - tileData.timeStamp;

	/* pass */

	return false;
}
