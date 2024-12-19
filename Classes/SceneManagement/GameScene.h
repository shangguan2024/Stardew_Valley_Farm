#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
#include "ResourceManagement/Texture.h"
#include <cmath>

class GameScene : public cocos2d::Scene {
protected:
    // 初始化场景
    virtual bool init();
    virtual void initConstants();

    // 鼠标滚动监听器
    void registerMouseScrollListener();
    void onMouseScroll(cocos2d::EventMouse* event);

    // 鼠标点击监听器
    void onMouseClick(cocos2d::EventMouse::MouseButton mouseButton);

    // 每一帧被自动调用的 update 方法
    virtual void update(float delta);

    // 转变坐标成瓦片坐标
    cocos2d::Vec2 convertToTileCoords(const cocos2d::Vec2& pos);
    bool setCameraCenter(const cocos2d::Vec3&);

    // 定义摄像机
    float fov = CAMERA_FOV;
    cocos2d::Camera* camera;
    cocos2d::TMXTiledMap* tilemap;

    MapName mapName; // enum class MapName
    std::string tileMapPath;
};

#endif
