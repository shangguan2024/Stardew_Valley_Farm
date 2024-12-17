#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"


class GameScene : cocos2d::Scene
{

public:
    // ��������
    static cocos2d::Scene *createScene();

    // ��ʼ������
    virtual bool init();

    // ������������
    void registerMouseScrollListener();
    void onMouseScroll(cocos2d::EventMouse *event);
    void onMouseClick(cocos2d::EventMouse::MouseButton mouseButton);

    // ÿһ֡���Զ����õ� update ����
    virtual void update(float delta);

    // ת���������Ƭ����
    cocos2d::Vec2 convertToTileCoords(const cocos2d::Vec2 &pos);

    CREATE_FUNC(GameScene); // �Զ��ͷ�

private:
    // ���������
    cocos2d::Camera *_camera;

};

#endif
