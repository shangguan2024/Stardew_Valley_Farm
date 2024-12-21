#include "FarmYardMap.h"

FarmYardMap::FarmYardMap()
{
    init();
}

FarmYardMap::~FarmYardMap()
{
    if (tileMap) {
        // 销毁 TMXTiledMap 对象
        tileMap->removeFromParent();  // 从父节点移除，确保不再引用
        tileMap = nullptr;  // 防止悬空指针
    }
}

void FarmYardMap::initContants()
{
	mapName = MapName::FarmYard;
	tileMapPath = Resources::FarmYardMap;
    musicPath = Audio::spring_am;
}
