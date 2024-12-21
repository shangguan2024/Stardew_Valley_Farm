#include "MapDataManager.h"
#include "GameTime/GameTime.h"

USING_NS_CC;

MapDataManager* MapDataManager::instance = nullptr;

MapDataManager::MapDataManager()
{
}

MapDataManager::~MapDataManager()
{
}

MapDataManager* MapDataManager::getInstacne()
{
	if (!instance) {
		instance = new MapDataManager();
	}
	return instance;
}

std::vector<MapDataManager::TileData>& MapDataManager::getTileData(MapName mapName)
{
	return tiles[mapName];
}

// return (tileData has changed ? true : false);
bool MapDataManager::updateTileData(TileData& tileData)
{
	int deltaTime = GameTime::getInstance()->getTimeStamp() - tileData.timeStamp;

	/* pass */

	return false;
}
