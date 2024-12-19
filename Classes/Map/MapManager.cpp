#include "MapManager.h"

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
