#include "GameScene.h"
#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"

USING_NS_CC;

// ��ʼ������
bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	initConstants();

	// ������Ƭ��ͼ
	// tileMap = TMXTiledMap::create(tileMapPath);
	if (!tileMap) {
		CCLOG("Failed to load tile map");
		return false;
	}
	this->addChild(tileMap->tileMap);
	tileMap->tileMap->setPosition(0, 0);
	tileMap->tileMap->setCameraMask(static_cast<unsigned short>(CameraFlag::USER1));

	// ���������
	auto winSize = Director::getInstance()->getWinSize();
	float zEye = Director::getInstance()->getZEye();

	camera = Camera::createPerspective(fov, winSize.width / winSize.height, 10, zEye + winSize.height / 2.0f);
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera);
	// ��ʼ��������߶�
	Vec3 currentCameraPos = camera->getPosition3D();
	currentCameraPos.z = CAMERA_Z;
	Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.0f));

	// ���� Meta Ϊ���ɼ���
	auto tileLayer = tileMap->getLayer("Meta");
	tileLayer->setVisible(false);
	tileLayer->setLocalZOrder(255);

	// ���س�����
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
	// ��ȡ������� x �� y ����
	float spawnX = spawnPoint["x"].asFloat();
	float spawnY = spawnPoint["y"].asFloat();
	CCLOG("Spawn point coordinates: (%f, %f)", spawnX, spawnY);

	// �ڳ����㴴�����
	auto player = Player::getInstance();
	this->addChild(player, 1, "player");
	player->setPosition(spawnX, spawnY);
	player->setCameraMask(unsigned short(CameraFlag::USER1));
	setCameraCenter();

	// UI
	auto camera = Camera::create();
	camera->setCameraFlag(CameraFlag::DEFAULT);
	this->addChild(camera);
	this->addChild(UIManager::getInstance());
	UIManager::getInstance()->setCameraMask(static_cast<unsigned short>(CameraFlag::DEFAULT));

	// ������ע�������ֺ�������¼�������
	registerMouseScrollListener();
	InputManager::getInstance()->registerMouseCallbackFunc(MouseControlMode::SCENE, [this](cocos2d::EventMouse::MouseButton mouseButton) {
		this->onMouseClick(mouseButton);
		});
	InputManager::getInstance()->setCurrentMouseControlMode(MouseControlMode::SCENE);

	// ����ÿ֡���º���
	this->scheduleUpdate();

	return true;
}

Vec2 GameScene::convertToTileCoords(const Vec2 pos)
{
	// ����ҵ���λ��ת��Ϊ��Ƭ����
	Size tilemapSize = tileMap->getMapSize();
	Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH),
		int((tilemapSize.height * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

	return tile;
}

bool GameScene::setCameraCenter()
{
	Vec3 currentCameraPos = camera->getPosition3D();

	// ��������ͷĿ��λ�� �� ƽ���ƶ������
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
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 1.0f)); // ƽ��ϵ��
	return true;
}

void GameScene::registerMouseScrollListener()
{
	// ��������¼�������
	auto listener = EventListenerMouse::create();
	listener->onMouseScroll = CC_CALLBACK_1(GameScene::onMouseScroll, this);

	// ��ȡ�¼��ַ�������Ӽ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// �������¼��ص�
void GameScene::onMouseScroll(cocos2d::EventMouse* event)
{
	auto scrollDelta = event->getScrollY(); // ��ȡ��������
	CCLOG("Mouse Scroll Delta: %f", scrollDelta);
	// �����������λ��
	Vec3 currentCameraPos = camera->getPosition3D();
	// ��������ͷĿ��λ��
	currentCameraPos.z += 16.0f * scrollDelta;
	if (currentCameraPos.z > 384.0f)
		currentCameraPos.z = 384.0f;
	if (currentCameraPos.z < 128.0f)
		currentCameraPos.z = 128.0f;
	Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
	// ƽ���ƶ������
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.8f));
	setCameraCenter();
}

// ������¼��ص�
void GameScene::onMouseClick(cocos2d::EventMouse::MouseButton mouseButton)
{
	Player* player = Player::getInstance();
	InputManager* inputManager = InputManager::getInstance();


	// ��ȡ��Ƭͼ��
	auto tileLayer = tileMap->getLayer("Meta");
	auto groundLayer = tileMap->getLayer("Ground");
	if (!tileLayer || !groundLayer) {
		CCLOG("Layer not found");
		return;
	}

	// �����ҵĵ�ǰλ�ò�ת��Ϊ��Ƭ����
	Vec2 currentPosition = player->getPosition();
	Vec2 currenttile = convertToTileCoords(currentPosition);

	// ��ȡ�����λ��
	auto Location = inputManager->getMousePosition(MouseControlMode::SCENE);
	// ����ƫ����
	Vec2 screenCenter = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	Vec2 offset = Vec2(currentPosition.x - screenCenter.x, currentPosition.y + screenCenter.y);
	offset.x += Location->x;
	offset.y -= Location->y;
	// ������λ��ת��Ϊ��Ƭ����
	Vec2 mousetile = convertToTileCoords(offset);

	// �ж�������İ�ť
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
	PlayerController::getInstance()->update();
	Player* player = Player::getInstance();

	// ��ȡ��Ƭͼ��
	auto tileLayer = tileMap->getLayer("Meta");
	if (!tileLayer) {
		CCLOG("Layer not found");
		return;
	}

	bool playerMoved = false;

	// ����ƶ�
	if (player->getDirection().x) {
		// �����ҵĵ�ǰλ�ò�ת��Ϊ��Ƭ����
		Vec2 currentPosition = player->getPosition();
		Vec2 currenttile = convertToTileCoords(currentPosition);

		// ������º��λ��
		Vec2 newPosition = player->getPosition() + Vec2(player->getDirection().x, 0) * player->getSpeed() * delta;

		// ��ȡ���Ŀ��λ�õ���ƬGID
		int tileGID = tileLayer->getTileGIDAt(convertToTileCoords(newPosition));

		// �������Ƭ��ͨ�У���������λ��
		if (!tileGID) {
			player->setPosition(newPosition);
			playerMoved = true;
		}
		else {
			auto xxx = tileMap->getPropertiesForGID(tileGID);
			if (xxx.find(TILE_COLLIDABLE) == xxx.end()) {
				player->setPosition(newPosition);
				playerMoved = true;
			}
		}
	}

	if (player->getDirection().y) {
		// �����ҵĵ�ǰλ�ò�ת��Ϊ��Ƭ����
		Vec2 currentPosition = player->getPosition();
		Vec2 currenttile = convertToTileCoords(currentPosition);

		// ������º��λ��
		Vec2 newPosition = player->getPosition() + Vec2(0, player->getDirection().y) * player->getSpeed() * delta;

		// ��ȡ���Ŀ��λ�õ���ƬGID
		int tileGID = tileLayer->getTileGIDAt(convertToTileCoords(newPosition));

		// �������Ƭ��ͨ�У���������λ��
		if (!tileGID) {
			player->setPosition(newPosition);
			playerMoved = true;
		}
		else {
			auto xxx = tileMap->getPropertiesForGID(tileGID);
			if (xxx.find("Collidable") == xxx.end()) {
				player->setPosition(newPosition);
				playerMoved = true;
			}
		}
	}

	if (playerMoved) {
		// �����������λ��
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

			// �л���Ŀ���ͼ
			// switchToMap(targetMap, spawnX, spawnY);
			break;
		}
	}
}
