#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"

class MapManager {
public:
	MapManager(const MapManager&) = delete;
	MapManager operator=(const MapManager&) = delete;

	struct TileData {
		cocos2d::Vec2 position;
		TileType tileType;
		SeedType seedType;
		int timeStamp;
	};

	static MapManager* getInstacne();

	std::vector<TileData>& getTileData(MapName mapName);

	static bool updateTileData(TileData& tileData);

private:
	MapManager();
	~MapManager();

	static MapManager* instance;

	std::unordered_map<MapName, std::vector<TileData>> tiles;
};

#endif
