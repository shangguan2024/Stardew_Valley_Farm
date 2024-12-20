#include "GameScene.h"
#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"
#include "SceneManager.h"
#include "FarmYardScene.h"
#include "BeachScene.h"

USING_NS_CC;

void GameScene::onEnter()
{
	Scene::onEnter();

	// 创建并注册鼠标滚轮和鼠标点击事件监听器
	registerMouseScrollListener();
	// InputManager::getInstance()->registerMouseCallbackFunc(MouseControlMode::SCENE, [this](cocos2d::EventMouse::MouseButton mouseButton) {
	//	this->onMouseClick(mouseButton);
	//	});
	// InputManager::getInstance()->setCurrentMouseControlMode(MouseControlMode::SCENE);

	// 启动每帧更新函数
	this->scheduleUpdate();
}

void GameScene::onExit()
{
	Scene::onExit();

	unRegisterMouseScrollListener();
	// InputManager::getInstance()->popCurrentMouseControlMode();
	this->unscheduleUpdate();
}

// 初始化场景
bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	initConstants();

	// 瓦片地图
	this->addChild(tileMap->tileMap);
	tileMap->tileMap->setPosition(0, 0);
	tileMap->tileMap->setCameraMask(static_cast<unsigned short>(CameraFlag::USER1));

	// 创建摄像机
	auto winSize = Director::getInstance()->getWinSize();
	float zEye = Director::getInstance()->getZEye();

	camera = Camera::createPerspective(fov, winSize.width / winSize.height, 10, zEye + winSize.height / 2.0f);
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera);
	// 初始化摄像机高度
	Vec3 currentCameraPos = camera->getPosition3D();
	currentCameraPos.z = CAMERA_Z;
	Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.0f));

	// 设置 Meta 为不可见层
	auto tileLayer = tileMap->getLayer("Meta");
	tileLayer->setVisible(false);
	tileLayer->setLocalZOrder(255);


	auto player = Player::getInstance();
	auto& enterPosition = PlayerController::getInstance()->enterPosition;
	// 在出生点创建玩家
	if (player->enterType() == PlayerEnterType::SPAWN) {
		// 加载出生点
		auto objectGroup = tileMap->getObjectGroup("Spawn");
		if (!objectGroup) {
			CCLOG("Failed to load object layer: Spawn");
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
		enterPosition = Vec2(spawnX, spawnY);
	}
	else if (player->enterType() == PlayerEnterType::FROM_PORTAL) {
		CCLOG("Player enter from portal.");
	}
	this->addChild(player, 1, "player");
	player->setPosition(enterPosition);
	player->setCameraMask(unsigned short(CameraFlag::USER1));
	setCameraCenter();

	// UI
	auto camera = Camera::create();
	camera->setCameraFlag(CameraFlag::DEFAULT);
	this->addChild(camera);
	this->addChild(UIManager::getInstance());
	UIManager::getInstance()->setCameraMask(static_cast<unsigned short>(CameraFlag::DEFAULT));

	return true;
}

Vec2 GameScene::convertToTileCoords(const Vec2 pos)
{
	// 将玩家的新位置转换为瓦片坐标
	Size tilemapSize = tileMap->getMapSize();
	Vec2 tile = Vec2(static_cast<int>(pos.x / MAP_TILE_WIDTH),
		static_cast<int>((tilemapSize.height * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

	// 输出调试信息
	CCLOG("Position: (%f, %f)", pos.x, pos.y);
	CCLOG("Tile: (%d, %d)", (int)tile.x, (int)tile.y);
	CCLOG("Tilemap Size: (%f, %f)", tilemapSize.width, tilemapSize.height);
	CCLOG("Map Tile Width: %d, Map Tile Height: %d", MAP_TILE_WIDTH, MAP_TILE_HEIGHT);

	return tile;
}

bool GameScene::setCameraCenter()
{
	Vec3 currentCameraPos = camera->getPosition3D();

	// 计算摄像头目标位置 并 平滑移动摄像机
	Vec2 leftUpMargin, rightDownMargin,
		target(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y);

	const auto& mapblock = tileMap->getMapSize();
	const auto& tilesize = tileMap->getTileSize();
	const auto& winSize = Director::getInstance()->getWinSize();
	auto mapsize = Size(mapblock.width * tilesize.width, mapblock.height * tilesize.height);

	// default fov = 60 deg
	const auto& aspect_ratio = winSize.width / winSize.height;
	const auto& fov2z = 2 * currentCameraPos.z * tan(60.0 / 180 * 3.14 / 2);
	Size visibleSize = Size(fov2z * aspect_ratio, fov2z);
	leftUpMargin = visibleSize / 2;
	rightDownMargin = mapsize - visibleSize / 2;

	if (leftUpMargin.x > rightDownMargin.x || leftUpMargin.y > rightDownMargin.y)
		return false;

	if (target.x < leftUpMargin.x) {
		target.x = leftUpMargin.x;
	}
	else if (target.x > rightDownMargin.x) {
		target.x = rightDownMargin.x;
	}
	if (target.y < leftUpMargin.y) {
		target.y = leftUpMargin.y;
	}
	else if (target.y > rightDownMargin.y) {
		target.y = rightDownMargin.y;
	}

	Vec3 targetCameraPos(target.x, target.y, currentCameraPos.z);
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 1.0f)); // 平滑系数
	return true;
}

void GameScene::registerMouseScrollListener()
{
	// 创建鼠标滚动事件监听器
	mouseScrollListener = EventListenerMouse::create();
	mouseScrollListener->onMouseScroll = CC_CALLBACK_1(GameScene::onMouseScroll, this);

	// 获取事件分发器并添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseScrollListener, this);
}

void GameScene::unRegisterMouseScrollListener()
{
	// 移除鼠标滚动事件监听器
	if (mouseScrollListener) {
		_eventDispatcher->removeEventListener(mouseScrollListener);
		mouseScrollListener = nullptr;
	}
}

// 鼠标滚轮事件回调
void GameScene::onMouseScroll(cocos2d::EventMouse* event)
{
	auto scrollDelta = event->getScrollY(); // 获取滚动增量
	CCLOG("Mouse Scroll Delta: %f", scrollDelta);
	// 计算摄像机的位置
	Vec3 currentCameraPos = camera->getPosition3D();
	// 计算摄像头目标位置
	currentCameraPos.z += 16.0f * scrollDelta;
	if (currentCameraPos.z > 384.0f)
		currentCameraPos.z = 384.0f;
	if (currentCameraPos.z < 128.0f)
		currentCameraPos.z = 128.0f;
	Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
	// 平滑移动摄像机
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.8f));
	setCameraCenter();
}

// 鼠标点击事件回调
void GameScene::onMouseClick(cocos2d::EventMouse::MouseButton mouseButton)
{
	Player* player = Player::getInstance();
	InputManager* inputManager = InputManager::getInstance();


	// 获取瓦片图层
	auto tileLayer = tileMap->getLayer("Meta");
	auto groundLayer = tileMap->getLayer("Ground");
	if (!tileLayer || !groundLayer) {
		CCLOG("Layer not found");
		return;
	}

	// 获得玩家的当前位置并转换为瓦片坐标
	Vec2 currentPosition = player->getPosition();
	Vec2 currenttile = convertToTileCoords(currentPosition);

	// 获取鼠标点击位置
	auto Location = inputManager->getMousePosition(MouseControlMode::SCENE);
	// 计算偏移量
	Vec2 screenCenter = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	Vec2 offset = Vec2(currentPosition.x - screenCenter.x, currentPosition.y + screenCenter.y);
	offset.x += Location->x;
	offset.y -= Location->y;
	// 将鼠标的位置转换为瓦片坐标
	Vec2 mousetile = convertToTileCoords(offset);

	// 判断鼠标点击的按钮
	if (mouseButton == EventMouse::MouseButton::BUTTON_LEFT) {
		CCLOG("Left mouse button clicked at: (%f, %f)", mousetile.x, mousetile.y);
	}
	else if (mouseButton == EventMouse::MouseButton::BUTTON_RIGHT) {
		CCLOG("Right mouse button clicked at: (%f, %f)", mousetile.x, mousetile.y);
	}

	tileMap->interactTile(currentPosition, mousetile, mouseButton);
}

void GameScene::update(float delta)
{
	Player* player = Player::getInstance();
	if (player->isFreeze())return;
	PlayerController::getInstance()->update();

	// 获取瓦片图层
	auto tileLayer = tileMap->getLayer("Meta");
	if (!tileLayer) {
		CCLOG("Layer not found");
		return;
	}

	bool playerMoved = false;

	// 玩家移动
	if (player->getDirection().x) {
		// 获得玩家的当前位置并转换为瓦片坐标
		Vec2 currentPosition = player->getPosition();
		Vec2 currenttile = convertToTileCoords(currentPosition);

		// 计算更新后的位置
		Vec2 newPosition = player->getPosition() + Vec2(player->getDirection().x, 0) * player->getSpeed() * delta;

		// 获取玩家目标位置的瓦片GID
		int tileGID = tileLayer->getTileGIDAt(convertToTileCoords(newPosition));

		// 如果该瓦片可通行，则更新玩家位置
		if (!tileGID) {
			player->setPosition(newPosition);
			playerMoved = true;
		}
		else {
			auto properties = tileMap->getPropertiesForGID(tileGID);
			if (properties.find(TILE_COLLIDABLE) == properties.end()) {
				player->setPosition(newPosition);
				playerMoved = true;
			}
		}
	}

	if (player->getDirection().y) {
		// 获得玩家的当前位置并转换为瓦片坐标
		Vec2 currentPosition = player->getPosition();
		Vec2 currenttile = convertToTileCoords(currentPosition);

		// 计算更新后的位置
		Vec2 newPosition = player->getPosition() + Vec2(0, player->getDirection().y) * player->getSpeed() * delta;

		// 获取玩家目标位置的瓦片GID
		int tileGID = tileLayer->getTileGIDAt(convertToTileCoords(newPosition));

		// 如果该瓦片可通行，则更新玩家位置
		if (!tileGID) {
			player->setPosition(newPosition);
			playerMoved = true;
		}
		else {
			auto properties = tileMap->getPropertiesForGID(tileGID);
			if (properties.find("Collidable") == properties.end()) {
				player->setPosition(newPosition);
				playerMoved = true;
			}
		}
	}

	if (playerMoved) {
		// 计算摄像机的位置
		setCameraCenter();
		checkPlayerEnterPortal(player->getPosition());
	}
}

void GameScene::checkPlayerEnterPortal(const Vec2 position)
{
	auto portalGroup = tileMap->getObjectGroup("Portals");
	if (!portalGroup) return;

	auto portalObjects = portalGroup->getObjects();
	for (const auto& obj : portalObjects) {
		auto portalData = obj.asValueMap();
		float x = portalData["x"].asFloat();
		float y = portalData["y"].asFloat();
		float width = portalData["width"].asFloat();
		float height = portalData["height"].asFloat();

		cocos2d::Rect portalRect(x, y, width, height);
		if (portalRect.containsPoint(position)) {
			std::string targetMap = portalData["target_map"].asString();
			float spawnX = portalData["spawn_x"].asFloat();
			float spawnY = portalData["spawn_y"].asFloat();
			CCLOG("Player entered portal to map: %s", targetMap.c_str());

			// 先这么写着
			// 切换到目标地图
			// switchToMap(targetMap, spawnX, spawnY);
			Player::getInstance()->freeze();
			Player::getInstance()->removeFromParent();
			PlayerController::getInstance()->enterPosition = Vec2(spawnX, spawnY);
			Player::getInstance()->setEnterType(PlayerEnterType::FROM_PORTAL);
			UIManager::getInstance()->removeFromParent();
			Scene* scene = nullptr;
			if(targetMap == "FarmYard") {
				scene = FarmYardScene::createScene();
			}
			else {
				scene = BeachScene::createScene();
			}
			Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, scene, cocos2d::Color3B::WHITE));
			break;
		}
	}
}
