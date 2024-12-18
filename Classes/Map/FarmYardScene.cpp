/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.cpp
 * File Function: FarmYardScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/5
 ****************************************************************/
#include "../Player/Player.h"
#include "FarmYardScene.h"
#include "FarmHouseScene.h"
#include "../NPC/ChatLayer.h"
#include "../NPC/NPC.h"

USING_NS_CC;

// 创建场景
Scene* FarmYardScene::createScene()
{
	auto scene = Scene::create();
	auto farmlayer = FarmYardScene::create();
	scene->addChild(farmlayer, 0);
	return scene;
}

// 初始化场景
bool FarmYardScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// 创建计时
	GameTime::getInstance()->start();

	// 创建摄像机
	camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	cocos2d::Vec3 currentPos = camera->getPosition3D();
	currentPos.z = DEFAULT_VIEW_HEIGHT;
	camera->setPosition3D(currentPos);
	this->addChild(camera);

	// 加载瓦片地图
	auto FarmYard = TMXTiledMap::create("Maps/FarmYardScene.tmx");
	if (!FarmYard) {
		CCLOG("Failed to load tile map");
		return false;
	}
	FarmYard->getLayer("Meta")->setVisible(false);

	this->addChild(FarmYard, 0, "FarmYard");
	FarmYard->setPosition(0, 0);
	FarmYard->setCameraMask(unsigned short(CameraFlag::USER1));

	// 获取地图的基础属性
	auto objectGroup = FarmYard->getObjectGroup("Event");
	if (!objectGroup) {
		CCLOG("Failed to load object layer: Event");
		return false;
	}

	auto spawnPoint = objectGroup->getObject("SpawnPoint");
	auto yardToHouse = objectGroup->getObject("YardToHouse");
	auto yardToTown = objectGroup->getObject("YardToTown");
	if (spawnPoint.empty()|| yardToHouse.empty() || yardToTown.empty()) {
		CCLOG("SpawnPoint not found in Event layer.");
		return false;
	}

	// 获取 YardToHouse 的位置和大小
	float x = yardToHouse["x"].asFloat();
	float y = yardToHouse["y"].asFloat();
	float width = yardToHouse["width"].asFloat();
	float height = yardToHouse["height"].asFloat();

	// 创建一个矩形表示 YardToHouse 区域
	yardToHouseRect.setRect(x, y, width, height);

	// 获取 YardToTown 的位置和大小
	x = yardToTown["x"].asFloat();
	y = yardToTown["y"].asFloat();
	width = yardToTown["width"].asFloat();
	height = yardToTown["height"].asFloat();

	// 创建一个矩形表示 YardToTown 区域
	yardToTownRect.setRect(x, y, width, height);

	// 提取出生点的 x 和 y 坐标
	float spawnX = spawnPoint["x"].asFloat();
	float spawnY = spawnPoint["y"].asFloat();

	auto player = Player::getInstance();
	player->init();
	this->addChild(player, 1, "player");
	player->setPosition(spawnX, spawnY);
	player->setCameraMask(unsigned short(CameraFlag::USER1));

	targettile = cocos2d::Sprite::create("Items/DrySoil.png");
	targettile->setAnchorPoint(Vec2(0, 0));
	this->addChild(targettile, 1, "targettile");
	targettile->setCameraMask(unsigned short(CameraFlag::USER1));

	// 创建并注册鼠标滚轮和鼠标点击事件监听器
	registerMouseScrollListener();
	registerMouseClickListener();

	// 启动每帧更新函数
	this->scheduleUpdate();

	return true;
}

Vec2 FarmYardScene::convertToTileCoords(const Vec2& pos)
{
	// 将玩家的新位置转换为瓦片坐标
	Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH), int((FARMYARD_MAP_HEIGHT * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

	return tile;
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
	Vec3 currentCameraPos = camera->getPosition3D();

	if ((currentCameraPos.z <= MIN_VIEW_HEIGHT && scrollDelta < 0) ||
		(currentCameraPos.z >= MAX_VIEW_HEIGHT && scrollDelta > 0))
		return;

	// 计算摄像头目标位置
	Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z + 100 * scrollDelta);
	// 平滑移动摄像机
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f));
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

	// 获取瓦片图层
	auto tileLayer = FarmYard->getLayer("Meta");
	auto groundLayer = FarmYard->getLayer("Ground");
	if (!tileLayer || !groundLayer) {
		CCLOG("Layer not found");
		return;
	}

	// 判断鼠标点击的按钮
	auto mouseButton = event->getMouseButton();
	if (mouseButton == EventMouse::MouseButton::BUTTON_LEFT) {
		CCLOG("Left mouse button clicked");
		// 执行左键点击相关操作
	}
	else if (mouseButton == EventMouse::MouseButton::BUTTON_RIGHT) {
		CCLOG("Right mouse button clicked");
		// 执行右键点击相关操作
	}

	// 丰富交互逻辑

}

void FarmYardScene::update(float delta)
{
	Player* player = Player::getInstance();

	// 获取 FarmYard 地图对象
	auto FarmYard = (TMXTiledMap*)this->getChildByName("FarmYard");

	// 计算摄像机的位置
	Vec3 currentCameraPos = camera->getPosition3D();

	// 获得玩家的当前位置并转换为瓦片坐标
	Vec2 currentPosition = player->getPosition();

	// 获取瓦片图层
	auto tileLayer = FarmYard->getLayer("Meta");
	if (!tileLayer) {
		CCLOG("Layer not found");
		return;
	}

	// 计算更新后的位置
	Vec2 newPosition = currentPosition + player->getDirection() * player->getSpeed() * delta;

	// 获取玩家目标位置的瓦片GID
	int tileGID = tileLayer->getTileGIDAt(convertToTileCoords(newPosition));

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

	if (yardToHouseRect.containsPoint(newPosition)) {
		// 在切换场景之前，先禁用更新
		this->unscheduleUpdate();

		this->removeChild(player);
		player->resetInit();
		Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, FarmHouseScene::createScene(), cocos2d::Color3B::WHITE));
	}
	else if (yardToTownRect.containsPoint(newPosition)) {
		// 在切换场景之前，先禁用更新
		this->unscheduleUpdate();

		this->removeChild(player);
		player->resetInit();
		Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, FarmHouseScene::createScene(), cocos2d::Color3B::WHITE));
	}

	Vec2 newtile = convertToTileCoords(newPosition);
	Vec2 faceto = player->getFaceto();
	targettile->setPosition(Vec2((newtile.x + faceto.x) * MAP_TILE_WIDTH, (FARMYARD_MAP_HEIGHT - newtile.y+ faceto.y) * MAP_TILE_HEIGHT));

#if 0

	timeLabel->setPosition(Vec2(camera->getPosition3D().x + Director::getInstance()->getVisibleSize().width / 2 - timeLabel->getContentSize().width, camera->getPosition3D().y + Director::getInstance()->getVisibleSize().height / 2 - timeLabel->getContentSize().height));
	this->addChild(timeLabel, 10, "timelabel");
	timeLabel->setCameraMask(unsigned short(CameraFlag::USER1));

	// 添加时间显示的背景
	auto removelabel1 = this->getChildByName("layercolor");
	if (removelabel1 != nullptr)
	{
		removelabel1->removeFromParentAndCleanup(true);
	}
	auto layercolor = LayerColor::create(Color4B(0, 255, 0, 128));
	layercolor->setContentSize(Size(timeLabel->getContentSize().width, timeLabel->getContentSize().height + 5));
	layercolor->setAnchorPoint(Vec2(0, 0));
	layercolor->setPosition(timeLabel->getPosition() - timeLabel->getContentSize() / 2);
	this->addChild(layercolor, 8, "layercolor");
	layercolor->setCameraMask(unsigned short(CameraFlag::USER1));

	auto removelabel2 = this->getChildByName("sprite");
	if (removelabel2 != nullptr)
	{
		removelabel2->removeFromParentAndCleanup(true);
	}
	auto sprite = Sprite::create("chatBox.png");
	sprite->setContentSize(layercolor->getContentSize());
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(timeLabel->getPosition() - timeLabel->getContentSize() / 2);
	this->addChild(sprite, 9, "sprite");
	sprite->setCameraMask(unsigned short(CameraFlag::USER1));

#endif

	// 计算摄像头目标位置
	Vec3 targetCameraPos(newPosition.x, newPosition.y, currentCameraPos.z);

	// 平滑移动摄像机
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f));// 平滑系数
}
