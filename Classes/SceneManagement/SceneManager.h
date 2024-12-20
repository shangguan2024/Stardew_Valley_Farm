// useless

#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "cocos2d.h"

class SceneManager {
public:
    static void init();  // 初始化场景管理器
    static void switchToScene(cocos2d::Scene* scene);  // 切换到指定场景
    static void pushScene(cocos2d::Scene* scene);  // 推入新场景（堆栈管理）
    static void popScene();  // 弹出当前场景，返回上一个场景
    static void cleanup();  // 清理当前场景和资源

    // 设置场景切换的过渡效果
    static cocos2d::TransitionScene* setSceneTransition(cocos2d::TransitionScene* transition);

    // 获取当前场景
    static cocos2d::Scene* getCurrentScene();

private:
    static cocos2d::Director* director;  // Cocos2d 的 Director 对象
    static cocos2d::TransitionScene* currentTransition;  // 当前场景过渡
};

#endif
