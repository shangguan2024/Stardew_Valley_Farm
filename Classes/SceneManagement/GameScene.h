#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
#include "ResourceManagement/Texture.h"
#include <cmath>

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
    bool setCameraCenter(const cocos2d::Vec3&);

    // ���������
    float fov = CAMERA_FOV;
    cocos2d::Camera* camera;
    cocos2d::TMXTiledMap* tilemap;

    MapName mapName; // enum class MapName
    std::string tileMapPath;
};

#endif
