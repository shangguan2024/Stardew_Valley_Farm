#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
#include "ResourceManagement/Texture.h"
#include "Map/MapBase.h"

class GameScene : public cocos2d::Scene {
protected:
    // 初始化场景
    virtual bool init();
    virtual void initConstants() = 0;

    // 鼠标滚动监听器
    void registerMouseScrollListener();
    void onMouseScroll(cocos2d::EventMouse* event);

    // 鼠标点击监听器
    void onMouseClick(cocos2d::EventMouse::MouseButton mouseButton);

    // 每一帧被自动调用的 update 方法
    virtual void update(float delta);

    void checkPlayerEnterPortal(const cocos2d::Vec2 position);

    // 转变坐标成瓦片坐标
    cocos2d::Vec2 convertToTileCoords(const cocos2d::Vec2 pos);
    bool setCameraCenter();

    // 定义摄像机
    float fov = CAMERA_FOV;
    cocos2d::Camera* camera;

    MapBase* tileMap;
};

#endif
