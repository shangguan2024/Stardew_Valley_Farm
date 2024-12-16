#include "SceneManager.h"

cocos2d::Director* SceneManager::director = nullptr;
cocos2d::Scene* SceneManager::currentScene = nullptr;
cocos2d::Scene* SceneManager::previousScene = nullptr;
cocos2d::TransitionScene* SceneManager::currentTransition = nullptr;

void SceneManager::init()
{
    director = cocos2d::Director::getInstance();
    currentScene = director->getRunningScene();
    previousScene = nullptr;
    currentTransition = nullptr;
}

void SceneManager::switchToScene(cocos2d::Scene* scene)
{
    if (scene != nullptr) {
        // 释放当前场景的资源
        if (currentScene != nullptr) {
            currentScene->onExit();
            director->purgeCachedData();
        }

        // 设置新场景
        previousScene = currentScene;
        currentScene = scene;

        // 切换场景
        if (currentTransition != nullptr) {
            director->replaceScene(currentTransition);
        }
        else {
            director->replaceScene(currentScene);
        }

        // 调用新场景的初始化
        currentScene->onEnter();
    }
}

void SceneManager::pushScene(cocos2d::Scene* scene)
{
    if (scene != nullptr) {
        // 保存当前场景
        previousScene = currentScene;
        currentScene = scene;

        // 在当前场景之上添加新场景
        director->pushScene(currentScene);
    }
}

void SceneManager::popScene()
{
    // 如果存在上一个场景，则弹出当前场景并返回上一个场景
    if (previousScene != nullptr) {
        director->popScene();
        currentScene = previousScene;
    }
}

void SceneManager::cleanup()
{
    // 清理当前场景资源
    if (currentScene != nullptr) {
        currentScene->onExit();
        director->purgeCachedData();
        currentScene = nullptr;
        previousScene = nullptr;
    }
}

void SceneManager::setSceneTransition(cocos2d::TransitionScene* transition)
{
    currentTransition = transition;
}

cocos2d::Scene* SceneManager::getCurrentScene()
{
    return currentScene;
}
