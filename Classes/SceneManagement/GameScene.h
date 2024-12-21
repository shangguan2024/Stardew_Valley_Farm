#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
#include "Map/MapBase.h"

class GameScene : public cocos2d::Scene {
protected:
	void onEnter() override;
	void onExit() override;

	// 初始化场景
	virtual bool init();
	virtual void initConstants() = 0;

	// 鼠标滚动监听器
	void registerMouseScrollListener();
	void unRegisterMouseScrollListener();
	void onMouseScroll(cocos2d::EventMouse* event);

	// 鼠标点击监听器
	void onMouseClick(cocos2d::EventMouse::MouseButton mouseButton);

	// 每一帧被自动调用的 update 方法
	virtual void update(float delta);

	void checkPlayerEnterPortal(const cocos2d::Vec2 position);

	cocos2d::Vec2 convertGLPosToTileCoord(const cocos2d::Vec2 pos);
	cocos2d::Vec2 getMouseTileCoord();
	bool setCameraCenter(const cocos2d::Vec3& cameraPos);

	const std::string& getSceneName() const;

	cocos2d::EventListenerMouse* mouseScrollListener;

	// 定义摄像机
	float fov = CAMERA_FOV;
	cocos2d::Camera* camera;

	MapBase* tileMap;

	std::string sceneName;
};

#endif
