#include "BeachMap.h"

BeachMap::BeachMap()
{
    init();
}

BeachMap::~BeachMap()
{
    if (tileMap) {
        // ���� TMXTiledMap ����
        tileMap->removeFromParent();  // �Ӹ��ڵ��Ƴ���ȷ����������
        tileMap = nullptr;  // ��ֹ����ָ��
    }
}

void BeachMap::initContants()
{
	mapName = MapName::Beach;
	tileMapPath = Texture::Beach;
}
