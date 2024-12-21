#ifndef __MAP_DATA_MANAGER_H__
#define __MAP_DATA_MANAGER_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"

class MapDataManager {
public:
	MapDataManager(const MapDataManager&) = delete;
	MapDataManager operator=(const MapDataManager&) = delete;

	struct TileData {
		cocos2d::Vec2 position;
		TileType tileType;
		SeedType seedType;
		int timeStamp;
	};

	static MapDataManager* getInstacne();

	std::vector<TileData>& getTileData(MapName mapName);

	static bool updateTileData(TileData& tileData);

private:
	MapDataManager();
	~MapDataManager();

	static MapDataManager* instance;

	std::unordered_map<MapName, std::vector<TileData>> tiles;
};

#endif
