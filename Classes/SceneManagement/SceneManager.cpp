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

// �ڵ�ǰ����֮������³���
void SceneManager::pushScene(cocos2d::Scene* scene)
{
	director->pushScene(scene);
}

// ���������һ���������򵯳���ǰ������������һ������
void SceneManager::popScene()
{
	director->popScene();
}

// ����ǰ������Դ
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
