#include "TestMap.h"

TestMap::TestMap()
{
    init();
}

TestMap::~TestMap()
{
    if (tileMap) {
        // 销毁 TMXTiledMap 对象
        tileMap->removeFromParent();  // 从父节点移除，确保不再引用
        tileMap = nullptr;  // 防止悬空指针
    }
}

void TestMap::initContants()
{
	mapName = MapName::Beach;
	tileMapPath = Resources::TestMap;

    musicPath = Audio::beach;
}
