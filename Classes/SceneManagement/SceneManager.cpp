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
        // �ͷŵ�ǰ��������Դ
        if (currentScene != nullptr) {
            currentScene->onExit();
            director->purgeCachedData();
        }

        // �����³���
        previousScene = currentScene;
        currentScene = scene;

        // �л�����
        if (currentTransition != nullptr) {
            director->replaceScene(currentTransition);
        }
        else {
            director->replaceScene(currentScene);
        }

        // �����³����ĳ�ʼ��
        currentScene->onEnter();
    }
}

void SceneManager::pushScene(cocos2d::Scene* scene)
{
    if (scene != nullptr) {
        // ���浱ǰ����
        previousScene = currentScene;
        currentScene = scene;

        // �ڵ�ǰ����֮������³���
        director->pushScene(currentScene);
    }
}

void SceneManager::popScene()
{
    // ���������һ���������򵯳���ǰ������������һ������
    if (previousScene != nullptr) {
        director->popScene();
        currentScene = previousScene;
    }
}

void SceneManager::cleanup()
{
    // ����ǰ������Դ
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
