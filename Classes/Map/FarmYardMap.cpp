#include "FarmYardMap.h"

FarmYardMap::FarmYardMap()
{
    init();
}

FarmYardMap::~FarmYardMap()
{
    if (tileMap) {
        // ���� TMXTiledMap ����
        tileMap->removeFromParent();  // �Ӹ��ڵ��Ƴ���ȷ����������
        tileMap = nullptr;  // ��ֹ����ָ��
    }
}

void FarmYardMap::initContants()
{
	mapName = MapName::FarmYard;
	tileMapPath = Resources::FarmYardMap;
    musicPath = Audio::spring_am;
}
