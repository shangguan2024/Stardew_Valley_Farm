#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
#include "ResourceManagement/Texture.h"
#include "Map/MapBase.h"

class GameScene : public cocos2d::Scene {
protected:
    // ��ʼ������
    virtual bool init();
    virtual void initConstants() = 0;

    // ������������
    void registerMouseScrollListener();
    void onMouseScroll(cocos2d::EventMouse* event);

    // �����������
    void onMouseClick(cocos2d::EventMouse::MouseButton mouseButton);

    // ÿһ֡���Զ����õ� update ����
    virtual void update(float delta);

    void checkPlayerEnterPortal(const cocos2d::Vec2 position);

    // ת���������Ƭ����
    cocos2d::Vec2 convertToTileCoords(const cocos2d::Vec2 pos);
    bool setCameraCenter();

    // ���������
    float fov = CAMERA_FOV;
    cocos2d::Camera* camera;

    MapBase* tileMap;
};

#endif
