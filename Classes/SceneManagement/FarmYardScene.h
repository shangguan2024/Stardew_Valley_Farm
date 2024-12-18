/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.h
 * File Function: FarmYardScene��Ķ���
 * Author:        ����
 * Update Date:   2024/12/5
 ****************************************************************/

#ifndef _FARM_YARD_SCENE_H_
#define _FARM_YARD_SCENE_H_

#include "cocos2d.h"

class FarmYardScene : public cocos2d::Scene
{
public:
    // ��������
    static cocos2d::Scene *createScene();

    // ��ʼ������
    virtual bool init();

    // ������������
    void registerMouseScrollListener();
    void onMouseScroll(cocos2d::EventMouse *event);

    // �����������
    void onMouseClick(cocos2d::EventMouse::MouseButton mouseButton);

    // ÿһ֡���Զ����õ� update ����
    virtual void update(float delta);

    // ת���������Ƭ����
    cocos2d::Vec2 convertToTileCoords(const cocos2d::Vec2 &pos);

    // ʵ�� FarmYardScene ��� create ����
    CREATE_FUNC(FarmYardScene);

private:
    // ���������
    cocos2d::Camera *_camera;
};

#endif // _FARM_YARD_SCENE_H_
