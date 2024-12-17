#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"


class GameScene : cocos2d::Scene
{

public:
    // 创建场景
    static cocos2d::Scene *createScene();

    // 初始化场景
    virtual bool init();

    // 鼠标滚动监听器
    void registerMouseScrollListener();
    void onMouseScroll(cocos2d::EventMouse *event);
    void onMouseClick(cocos2d::EventMouse::MouseButton mouseButton);

    // 每一帧被自动调用的 update 方法
    virtual void update(float delta);

    // 转变坐标成瓦片坐标
    cocos2d::Vec2 convertToTileCoords(const cocos2d::Vec2 &pos);

    CREATE_FUNC(GameScene); // 自动释放

private:
    // 定义摄像机
    cocos2d::Camera *_camera;

};

#endif
