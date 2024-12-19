#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();
    // 初始化场景
    virtual bool init();
    // 实现 MenuScene 类的 create 方法
    CREATE_FUNC(MainMenuScene);
};

#endif // __MENU_SCENE_H__
