/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.h
 * File Function: FarmYardScene类的定义
 * Author:        张翔
 * Update Date:   2024/12/5
 ****************************************************************/
#pragma once
#ifndef _FARM_YARD_SCENE_H_
#define _FARM_YARD_SCENE_H_

#include "cocos2d.h"


class FarmYardScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 鼠标滚动监听器
    void registerMouseScrollListener();
    void onMouseScroll(cocos2d::EventMouse* event);

    // 鼠标点击监听器
    void registerMouseClickListener();
    void onMouseClick(cocos2d::EventMouse* event);

    // 每一帧被自动调用的 update 方法
    virtual void update(float delta);

    // 实现 FarmYardScene 类的 create 方法
    CREATE_FUNC(FarmYardScene);

private:
    // 转变坐标成瓦片坐标
    cocos2d::Vec2 convertToTileCoords(const cocos2d::Vec2& pos);

    cocos2d::Camera* camera;         // 定义摄像机
    cocos2d::Sprite* targettile;     // 玩家正在处理的位置
    cocos2d::Rect yardToHouseRect;   // 由农场转入房子的判断框
    cocos2d::Rect yardToTownRect;    // 由农场转入城镇的判断框

};

#endif // _FARM_YARD_SCENE_H_
