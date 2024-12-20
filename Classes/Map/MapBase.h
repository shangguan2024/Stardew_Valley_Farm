#ifndef MAP_BASE_H
#define MAP_BASE_H

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"

class MapBase : public cocos2d::Node {
public:
    MapBase();
    virtual ~MapBase() = default;

    // ���µ�ͼ״̬
    virtual void update(float deltaTime);

    // ��ȡ�ߴ�
    cocos2d::Size getMapSize() const;
    cocos2d::Size getTileSize() const;

    // ��ȡ ObjectGroup
    cocos2d::TMXObjectGroup * getObjectGroup(const std::string& objectGroup) const;

    // ���� ObjectGroup ��ȡ Object
    cocos2d::ValueMap getObject(const std::string& objectGroup, const std::string& object) const;

    // ��ȡ��Ƭͼ��
    cocos2d::TMXLayer* getLayer(const std::string& layer) const;

    // ��ȡ��Ƭ����
    cocos2d::Sprite * getTileAt(const std::string& layer, const cocos2d::Vec2& position) const;
    cocos2d::ValueMap getPropertiesForGID(int GID) const;

    // ����ĳ��λ�õ���Ƭ״̬
    void setTileState(const cocos2d::Vec2& position, TileType tileType);

    // ����Ƭ����
    void interactTile(const cocos2d::Vec2& curPos, const cocos2d::Vec2& interactPos, cocos2d::EventMouse::MouseButton interactType);

    // ���浱ǰ��ͼ״̬
    // virtual void saveMapState(const std::string& filePath) = 0;

    // ���ص�ͼ״̬
    // virtual void loadMapState(const std::string& filePath) = 0;

    cocos2d::TMXTiledMap* tileMap;  // ���ڼ��غ���Ⱦ��ͼ

protected:
    // ��ʼ����ͼ
    bool init();
    virtual void initContants() = 0;

    MapName mapName;
    std::string tileMapPath;

};

#endif // MAP_BASE_H
