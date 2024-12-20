// useless

#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "cocos2d.h"

class SceneManager {
public:
    static void init();  // ��ʼ������������
    static void switchToScene(cocos2d::Scene* scene);  // �л���ָ������
    static void pushScene(cocos2d::Scene* scene);  // �����³�������ջ����
    static void popScene();  // ������ǰ������������һ������
    static void cleanup();  // ����ǰ��������Դ

    // ���ó����л��Ĺ���Ч��
    static cocos2d::TransitionScene* setSceneTransition(cocos2d::TransitionScene* transition);

    // ��ȡ��ǰ����
    static cocos2d::Scene* getCurrentScene();

private:
    static cocos2d::Director* director;  // Cocos2d �� Director ����
    static cocos2d::TransitionScene* currentTransition;  // ��ǰ��������
};

#endif
