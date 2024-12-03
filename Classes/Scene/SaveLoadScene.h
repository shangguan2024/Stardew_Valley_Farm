/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     SaveLoadScene.h
 * File Function: SaveLoadScene类的定义
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef __SAVE_LOAD_SCENE_H__
#define __SAVE_LOAD_SCENE_H__

#include "cocos2d.h"

class SaveLoadScene : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 MenuScene 类的 create 方法
    CREATE_FUNC(SaveLoadScene);
};

#endif // __SAVE_LOAD_SCENE_H__
