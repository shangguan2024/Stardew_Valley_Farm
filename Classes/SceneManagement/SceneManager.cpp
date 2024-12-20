// useless

#include "SceneManager.h"
#include "Player/Player.h"

cocos2d::Director* SceneManager::director = nullptr;
cocos2d::TransitionScene* SceneManager::currentTransition = nullptr;

void SceneManager::init()
{
	director = cocos2d::Director::getInstance();
	currentTransition = nullptr;
}

void SceneManager::switchToScene(cocos2d::Scene* scene)
{
	director->replaceScene(scene);
}

// 在当前场景之上添加新场景
void SceneManager::pushScene(cocos2d::Scene* scene)
{
	director->pushScene(scene);
}

// 如果存在上一个场景，则弹出当前场景并返回上一个场景
void SceneManager::popScene()
{
	director->popScene();
}

// 清理当前场景资源
void SceneManager::cleanup()
{
	auto currentScene = getCurrentScene();
	if (currentScene != nullptr) {
		currentScene->onExit();
		director->purgeCachedData();
	}
}

cocos2d::TransitionScene* SceneManager::setSceneTransition(cocos2d::TransitionScene* transition)
{
	return currentTransition = transition;
}

cocos2d::Scene* SceneManager::getCurrentScene()
{
	return director->getRunningScene();
}
