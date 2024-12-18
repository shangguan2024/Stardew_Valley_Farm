#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ResourceManagement/Texture.h"

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

    // 定义摄像机
    cocos2d::Camera* _camera;

    std::string sceneName;
    std::string tileMapPath;
};

#endif
