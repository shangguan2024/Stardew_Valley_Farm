#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ResourceManagement/Texture.h"

class GameScene : public cocos2d::Scene {
protected:
    // ��ʼ������
    virtual bool init();
    virtual void initConstants();

    // ������������
    void registerMouseScrollListener();
    void onMouseScroll(cocos2d::EventMouse* event);

    // �����������
    void onMouseClick(cocos2d::EventMouse::MouseButton mouseButton);

    // ÿһ֡���Զ����õ� update ����
    virtual void update(float delta);

    // ת���������Ƭ����
    cocos2d::Vec2 convertToTileCoords(const cocos2d::Vec2& pos);

    // ���������
    cocos2d::Camera* _camera;

    std::string sceneName;
    std::string tileMapPath;
};

#endif
