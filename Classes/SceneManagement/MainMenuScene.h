#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene {
public:
	// ��������
	static cocos2d::Scene* createScene();
	// ��ʼ������
	virtual bool init();
	// ʵ�� MenuScene ��� create ����
	CREATE_FUNC(MainMenuScene);
};

#endif // __MENU_SCENE_H__
