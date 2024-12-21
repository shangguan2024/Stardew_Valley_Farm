#include "TestMap.h"

TestMap::TestMap()
{
    init();
}

TestMap::~TestMap()
{
    if (tileMap) {
        // ���� TMXTiledMap ����
        tileMap->removeFromParent();  // �Ӹ��ڵ��Ƴ���ȷ����������
        tileMap = nullptr;  // ��ֹ����ָ��
    }
}

void TestMap::initContants()
{
	mapName = MapName::Beach;
	tileMapPath = Resources::TestMap;

    musicPath = Audio::beach;
}
