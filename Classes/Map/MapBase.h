#ifndef MAP_BASE_H
#define MAP_BASE_H

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"

class MapBase : public cocos2d::Node {
public:
    MapBase();
    virtual ~MapBase() = default;

    // 更新地图状态
    virtual void update(float deltaTime);

    // 获取尺寸
    cocos2d::Size getMapSize() const;
    cocos2d::Size getTileSize() const;

    // 获取 ObjectGroup
    cocos2d::TMXObjectGroup * getObjectGroup(const std::string& objectGroup) const;

    // 根据 ObjectGroup 获取 Object
    cocos2d::ValueMap getObject(const std::string& objectGroup, const std::string& object) const;

    // 获取瓦片图层
    cocos2d::TMXLayer* getLayer(const std::string& layer) const;

    // 获取瓦片数据
    cocos2d::Sprite * getTileAt(const std::string& layer, const cocos2d::Vec2& position) const;
    cocos2d::ValueMap getPropertiesForGID(int GID) const;

    // 设置某个位置的瓦片状态
    void setTileState(const cocos2d::Vec2& position, TileType tileType);

    // 与瓦片交互
    void interactTile(const cocos2d::Vec2& curPos, const cocos2d::Vec2& interactPos, cocos2d::EventMouse::MouseButton interactType);

    // 保存当前地图状态
    // virtual void saveMapState(const std::string& filePath) = 0;

    // 加载地图状态
    // virtual void loadMapState(const std::string& filePath) = 0;

    cocos2d::TMXTiledMap* tileMap;  // 用于加载和渲染地图

protected:
    // 初始化地图
    bool init();
    virtual void initContants() = 0;

    MapName mapName;
    std::string tileMapPath;

};

#endif // MAP_BASE_H
