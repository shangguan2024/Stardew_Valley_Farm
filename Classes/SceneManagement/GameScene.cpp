#include "GameScene.h"
#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "ResourceManagement/ResourceManager.h"
#include "ResourceManagement/AudioManager.h"
#include "UI/UIManager.h"
#include "SceneManager.h"
#include "TestScene.h"
#include "FarmYardScene.h"
#include "BeachScene.h"

USING_NS_CC;

void GameScene::onEnter()
{
	Scene::onEnter();

	// ������ע�������ֺ�������¼�������
	registerMouseScrollListener();
	InputManager::getInstance()->registerMouseCallbackFunc(sceneName, [this](cocos2d::EventMouse::MouseButton mouseButton) {
		this->onMouseClick(mouseButton);
		});
	InputManager::getInstance()->setCurrentMouseControlMode(sceneName);

	// ����ÿ֡���º���
	this->scheduleUpdate();
}

void GameScene::onExit()
{
	Scene::onExit();

	unRegisterMouseScrollListener();
	InputManager::getInstance()->resetCurrentMouseControlMode(sceneName);
	this->unscheduleUpdate();
}

// ��ʼ������
bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	initConstants();

	AudioManager::getInstance()->playMusic(Audio::beach);

	// ��Ƭ��ͼ
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


	auto player = Player::getInstance();
	auto& enterPosition = PlayerController::getInstance()->enterPosition;
	if (player->enterType() == PlayerEnterType::SPAWN) {
		// �ڳ����㴴�����
		auto objectGroup = tileMap->getObjectGroup("Spawn");
		if (!objectGroup) {
			CCLOG("Failed to load object layer: Spawn");
			return false;
		}
		auto spawnPoint = objectGroup->getObject("SpawnPoint");
		if (spawnPoint.empty()) {
			CCLOG("SpawnPoint not found in Spawn layer.");
			return false;
		}
		// ��ȡ������� x �� y ����
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
	setCameraCenter(camera->getPosition3D());

	// UI
	auto UICamera = Camera::create();
	UICamera->setCameraFlag(CameraFlag::DEFAULT);
	this->addChild(UICamera);
	this->addChild(UIManager::getInstance());
	UIManager::getInstance()->setCameraMask(static_cast<unsigned short>(CameraFlag::DEFAULT));

	return true;
}

Vec2 GameScene::convertGLPosToTileCoord(const Vec2 pos)
{
	// ����ҵ���λ��ת��Ϊ��Ƭ����
	Size tilemapSize = tileMap->getMapSize();
	Vec2 tile = Vec2(static_cast<int>(pos.x / MAP_TILE_WIDTH),
		static_cast<int>((tilemapSize.height * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

	// ���������Ϣ
	CCLOG("Position: (%f, %f)", pos.x, pos.y);
	CCLOG("Tile: (%d, %d)", (int)tile.x, (int)tile.y);
	// CCLOG("Tilemap Size: (%f, %f)", tilemapSize.width, tilemapSize.height);
	// CCLOG("Map Tile Width: %d, Map Tile Height: %d", MAP_TILE_WIDTH, MAP_TILE_HEIGHT);

	return tile;
}

Vec2 GameScene::getMouseTileCoord()
{
	auto cameraPos = camera->getPosition3D();
	Vec2 cameraPos2D(cameraPos.x, cameraPos.y);
	Vec2 winSize = Director::getInstance()->getWinSize();
	auto aspect_ratio = winSize.x / winSize.y;
	auto fov2z = 2 * cameraPos.z * tan(60.0 / 180 * acos(-1) / 2);
	Vec2 visibleSize = Size(fov2z * aspect_ratio, fov2z);
	auto mousePos = *InputManager::getInstance()->getMousePosition();
	Vec2 resCoord = cameraPos2D + (mousePos - winSize * 0.5) / winSize.length() * visibleSize.length();

	return convertGLPosToTileCoord(resCoord);
}

bool GameScene::setCameraCenter(const Vec3& cameraPos)
{
	// ��������ͷĿ��λ�� ��ƽ���ƶ������
	Vec2 leftUpMargin, rightDownMargin, target(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y);

	const auto& mapSize = tileMap->getMapSize();
	const auto& tileSize = tileMap->getTileSize();
	const auto& winSize = Director::getInstance()->getWinSize();
	auto mapsize = Size(mapSize.width * tileSize.width, mapSize.height * tileSize.height);

	// default fov = 60 deg
	const auto& aspect_ratio = winSize.width / winSize.height;
	const auto& fov2z = 2 * cameraPos.z * tan(60.0 / 180 * acos(-1) / 2);
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

	Vec3 targetCameraPos(target.x, target.y, cameraPos.z);
	camera->setPosition3D(cameraPos.lerp(targetCameraPos, 1.0f)); // ƽ��ϵ��
	return true;
}

const std::string& GameScene::getSceneName() const
{
	return sceneName;
}

void GameScene::registerMouseScrollListener()
{
	// �����������¼�������
	mouseScrollListener = EventListenerMouse::create();
	mouseScrollListener->onMouseScroll = CC_CALLBACK_1(GameScene::onMouseScroll, this);

	// ��ȡ�¼��ַ�������Ӽ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseScrollListener, this);
}

void GameScene::unRegisterMouseScrollListener()
{
	// �Ƴ��������¼�������
	if (mouseScrollListener) {
		_eventDispatcher->removeEventListener(mouseScrollListener);
		mouseScrollListener = nullptr;
	}
}

// �������¼��ص�
void GameScene::onMouseScroll(cocos2d::EventMouse* event)
{
	auto scrollDelta = event->getScrollY(); // ��ȡ��������
	// CCLOG("Mouse Scroll Delta: %f", scrollDelta);
	// �����������λ��
	Vec3 currentCameraPos = camera->getPosition3D();
	// ��������ͷĿ��λ��
	currentCameraPos.z += 16.0f * scrollDelta;
	if (!setCameraCenter(currentCameraPos))return;
	if (currentCameraPos.z > 384.0f)currentCameraPos.z = 384.0f;
	if (currentCameraPos.z < 128.0f)currentCameraPos.z = 128.0f;
	Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
	// ƽ���ƶ������
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.8f));
	setCameraCenter(currentCameraPos);
}

// ������¼��ص�
void GameScene::onMouseClick(cocos2d::EventMouse::MouseButton mouseButton)
{
	Player* player = Player::getInstance();
	InputManager* inputManager = InputManager::getInstance();

	// ��ȡ��Ƭͼ��
	auto tileLayer = tileMap->getLayer("Meta");

	// �����ҵĵ�ǰλ�ò�ת��Ϊ��Ƭ����
	auto playerTileCoord = convertGLPosToTileCoord(player->getPosition());

	// ��ȡ�����λ��
	auto mouseTileCoord = getMouseTileCoord();

	// �ж�������İ�ť
	if (mouseButton == EventMouse::MouseButton::BUTTON_LEFT) {
		CCLOG("Left mouse button clicked at: (%f, %f)", mouseTileCoord.x, mouseTileCoord.y);
	}
	else if (mouseButton == EventMouse::MouseButton::BUTTON_RIGHT) {
		CCLOG("Right mouse button clicked at: (%f, %f)", mouseTileCoord.x, mouseTileCoord.y);
	}

	tileMap->interactTile(playerTileCoord, mouseTileCoord, mouseButton);
}

void GameScene::update(float delta)
{
	Player* player = Player::getInstance();
	if (player->isFreeze())return;
	PlayerController::getInstance()->update();

	// ��ȡ��Ƭͼ��
	auto tileLayer = tileMap->getLayer("Meta");
	if (!tileLayer) {
		CCLOG("Meta layer not found");
		return;
	}

	// ����ƶ�
	auto tryMove = [&](const Vec2& direction) -> bool {
		if (direction == Vec2::ZERO)return false;
		// �����ҵĵ�ǰλ�ò�ת��Ϊ��Ƭ����
		Vec2 currentPosition = player->getPosition();
		Vec2 currenttile = convertGLPosToTileCoord(currentPosition);

		// ������º��λ��
		Vec2 newPosition = player->getPosition() + direction * player->getSpeed() * delta;

		// ��ȡ���Ŀ��λ�õ���ƬGID
		int tileGID = tileLayer->getTileGIDAt(convertGLPosToTileCoord(newPosition));

		// �������Ƭ��ͨ�У���������λ��
		if (!tileGID) {
			player->setPosition(newPosition);
			return true;
		}
		else {
			auto properties = tileMap->getPropertiesForGID(tileGID);
			if (properties.find("Collidable") == properties.end()) {
				player->setPosition(newPosition);
				return true;
			}
		}
		return false;
		};

	Vec2 moveX(player->getDirection().x, 0), moveY(0, player->getDirection().y);
	if (tryMove(moveX) | tryMove(moveY)) {
		setCameraCenter(camera->getPosition3D());
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

			// ����ôд��
			// �л���Ŀ���ͼ
			// switchToMap(targetMap, spawnX, spawnY);
			Player::getInstance()->freeze();
			Player::getInstance()->removeFromParent();
			PlayerController::getInstance()->enterPosition = Vec2(spawnX, spawnY);
			Player::getInstance()->setEnterType(PlayerEnterType::FROM_PORTAL);
			UIManager::getInstance()->removeFromParent();
			Scene* scene = nullptr;
			switch (ResourceManager::getInstance()->stringToMapNameEnum(targetMap)) {
			case MapName::FarmYard:
				scene = FarmYardScene::createScene();
				break;
			case MapName::Beach:
				scene = BeachScene::createScene();
				break;
			case MapName::Test:
				scene = TestScene::createScene();
				break;
			default:
				CCLOG("Invalid targetMap.");
				break;
			}
			Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, scene, cocos2d::Color3B::WHITE));
			break;
		}
	}
}
