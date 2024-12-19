#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"

class MapManager {
public:
	struct TileData {
		int x, y;
		std::string property;
		std::string state;
	};

	static MapManager* getInstacne();

	std::vector<TileData>& getTileData(MapName mapName);

private:
	MapManager();
	~MapManager();

	static MapManager* instance;

	std::unordered_map<MapName, std::vector<TileData>> tiles;
};

#endif
