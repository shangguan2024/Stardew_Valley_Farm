/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.cpp
 * File Function: FarmYardScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/5
 ****************************************************************/
#include "../Player/Player.h"
#include "FarmYardScene.h"

USING_NS_CC;

// 创建场景
Scene* FarmYardScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FarmYardScene::create();
	scene->addChild(layer);
	return scene;
}

// 初始化场景
bool FarmYardScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// 创建摄像机
	_camera = Camera::create();
	_camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(_camera);

	// 创建鼠标滚轮事件监听器
	auto listener = EventListenerMouse::create();
	listener->onMouseScroll = CC_CALLBACK_1(FarmYardScene::onMouseScroll, this);

	// 获取事件分发器并添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 加载瓦片地图
	auto FarmYard = TMXTiledMap::create("Maps/FarmYardScene.tmx");
	if (!FarmYard) {
		CCLOG("Failed to load tile map");
		return false;
	}

	auto tileLayer = FarmYard->getLayer("Meta");
	tileLayer->setVisible(false);

	this->addChild(FarmYard, 0, "FarmYard");
	FarmYard->setPosition(0, 0);
	FarmYard->setCameraMask(unsigned short(CameraFlag::USER1));

	// 获取地图的基础属性
	auto mapSize = FarmYard->getMapSize();
	auto tileSize = FarmYard->getTileSize();
	auto mapCenter = Vec2(mapSize.width * tileSize.width / 2, mapSize.height * tileSize.height / 2);

	auto objectGroup = FarmYard->getObjectGroup("Event");
	if (!objectGroup) {
		CCLOG("Failed to load object layer: Event");
		return false;
	}

	auto spawnPoint = objectGroup->getObject("SpawnPoint");
	if (spawnPoint.empty()) {
		CCLOG("SpawnPoint not found in Event layer.");
		return false;
	}

	// 提取出生点的 x 和 y 坐标
	float spawnX = spawnPoint["x"].asFloat();
	float spawnY = spawnPoint["y"].asFloat();
	CCLOG("Spawn point coordinates: (%f, %f)", spawnX, spawnY);

	auto player = Player::getInstance();
	this->addChild(player, 1, "player");
	player->setPosition(spawnX, spawnY);
	player->setCameraMask(unsigned short(CameraFlag::USER1));

	// 创建并注册鼠标滚轮和鼠标点击事件监听器
	registerMouseScrollListener();
	registerMouseClickListener();

	// 启动每帧更新函数
	this->scheduleUpdate();

	return true;
}

void FarmYardScene::registerMouseScrollListener()
{
	// 创建鼠标事件监听器
	auto listener = EventListenerMouse::create();
	listener->onMouseScroll = CC_CALLBACK_1(FarmYardScene::onMouseScroll, this);

	// 获取事件分发器并添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 鼠标滚轮事件回调
void FarmYardScene::onMouseScroll(cocos2d::EventMouse* event)
{
	auto scrollDelta = event->getScrollY();  // 获取滚动增量
	CCLOG("Mouse Scroll Delta: %f", scrollDelta);
	// 计算摄像机的位置
	Vec3 currentCameraPos = _camera->getPosition3D();
	// 计算摄像头目标位置
	Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
	// 平滑移动摄像机
	_camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f));
}

// 注册鼠标点击监听器
void FarmYardScene::registerMouseClickListener()
{
	// 创建鼠标点击事件监听器
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(FarmYardScene::onMouseClick, this);

	// 获取事件分发器并添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 鼠标点击事件回调
void FarmYardScene::onMouseClick(cocos2d::EventMouse* event)
{
	Player* player = Player::getInstance();

	// 获取 FarmYard 地图对象
	auto FarmYard = (TMXTiledMap*)this->getChildByName("FarmYard");
	Size mapSize = FarmYard->getMapSize();
	Size tileSize = FarmYard->getTileSize();

	// 获取瓦片图层
	auto tileLayer = FarmYard->getLayer("Meta");
	auto groundLayer = FarmYard->getLayer("Ground");
	if (!tileLayer || !groundLayer) {
		CCLOG("Layer not found");
		return;
	}

	// 获得玩家的当前位置并转换为瓦片坐标
	Vec2 currentPosition = player->getPosition();
	int playerX = currentPosition.x / tileSize.width;
	int playerY = (mapSize.height * tileSize.height - currentPosition.y) / tileSize.height;

	// 获取鼠标点击位置
	auto Location = event->getLocation();
	// 计算偏移量
	Vec2 screenCenter = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	Vec2 offset = Vec2(currentPosition.x - screenCenter.x, currentPosition.y + screenCenter.y);
	offset.x += Location.x;
	offset.y -= Location.y;
	// 将鼠标的位置转换为瓦片坐标
	int mouseX = offset.x / tileSize.width;
	int mouseY = (mapSize.height * tileSize.height - offset.y) / tileSize.height;
	// 计算玩家和鼠标之间的瓦片距离
	float distance = sqrt(pow(playerX - mouseX, 2) + pow(playerY - mouseY, 2));

	// 判断鼠标点击的按钮
	auto mouseButton = event->getMouseButton();
	if (mouseButton == EventMouse::MouseButton::BUTTON_LEFT) {
		CCLOG("Left mouse button clicked at: (%f, %f)", Location.x, Location.y);
		// 执行左键点击相关操作
	}
	else if (mouseButton == EventMouse::MouseButton::BUTTON_RIGHT) {
		CCLOG("Right mouse button clicked at: (%f, %f)", Location.x, Location.y);
		// 执行右键点击相关操作
	}

	// 判断距离是否小于交互范围（假设交互范围为 2）
	if (distance > 2) {
		CCLOG("Too far to interact");
	}
	else {
		// 获取鼠标位置的瓦片 GID
		int mouseGID = tileLayer->getTileGIDAt(Vec2(mouseX, mouseY));

		// 如果 GID 不为空，表示该位置可以交互
		if (mouseGID) {
			// 获取瓦片属性
			auto properties = FarmYard->getPropertiesForGID(mouseGID).asValueMap();
			if (!properties.empty()) {
				// 判断瓦片是否具有 "Plowable" 属性且为 true
				if (properties["Plowable"].asBool()) {
					// 执行交互操作
					CCLOG("Interacting with plowable tile");
				}
			}
		}
		else {
			CCLOG("Nothing to interact");
		}
	}
}

void FarmYardScene::update(float delta)
{
	Player* player = Player::getInstance();

	// 获取 FarmYard 地图对象
	auto FarmYard = (TMXTiledMap*)this->getChildByName("FarmYard");
	Size mapSize = FarmYard->getMapSize();
	Size tileSize = FarmYard->getTileSize();

	// 计算摄像机的位置
	Vec3 currentCameraPos = _camera->getPosition3D();

	// 获得玩家的当前位置并转换为瓦片坐标
	Vec2 currentPosition = player->getPosition();
	int playerX = currentPosition.x / tileSize.width;
	int playerY = (mapSize.height * tileSize.height - currentPosition.y) / tileSize.height;

	// 获取瓦片图层
	auto tileLayer = FarmYard->getLayer("Meta");
	if (!tileLayer) {
		CCLOG("Layer not found");
		return;
	}

	// 计算更新后的位置
	Vec2 newPosition = currentPosition + player->getDirection() * player->getSpeed() * delta;

	// 将玩家的新位置转换为瓦片坐标
	int tileX = newPosition.x / tileSize.width;
	int tileY = (mapSize.height * tileSize.height - newPosition.y) / tileSize.height;

	// 获取玩家目标位置的瓦片GID
	int tileGID = tileLayer->getTileGIDAt(Vec2(tileX, tileY));

	if (tileGID) {
		// 获取瓦片属性
		auto properties = FarmYard->getPropertiesForGID(tileGID).asValueMap();
		if (!properties.empty()) {
			// 判断瓦片是否具有 "Collidable" 属性且为 true
			if (properties["Collidable"].asBool()) {
				// 如果该瓦片不可通行，则直接返回，不更新玩家位置
				return;
			}
		}
	}

	// 更新玩家位置
	player->setPosition(newPosition);

	// 计算摄像头目标位置
	Vec3 targetCameraPos(newPosition.x, newPosition.y, currentCameraPos.z);

	// 平滑移动摄像机
	_camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f));// 平滑系数
}
