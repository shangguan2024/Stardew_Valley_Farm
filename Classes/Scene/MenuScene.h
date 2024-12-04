/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     MenuScene.h
 * File Function: MenuScene类的定义
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 MenuScene 类的 create 方法
    CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
