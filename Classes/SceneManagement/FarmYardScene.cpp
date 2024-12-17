/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.cpp
 * File Function: FarmYardScene���ʵ��
 * Author:        ����
 * Update Date:   2024/12/5
 ****************************************************************/
#include "FarmYardScene.h"
#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"
 // #include "../GameTime/GameTime.h"

USING_NS_CC;

// ��������
Scene* FarmYardScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FarmYardScene::create();
	scene->addChild(layer);
	return scene;
}

// ��ʼ������
bool FarmYardScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// ������ʱ
	// gametime = GameTime::getInstance();
	// gametime->start();

	// ���������
	_camera = Camera::create();
	_camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(_camera);

	// ������Ƭ��ͼ
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

	// ��ȡ��ͼ�Ļ�������
	auto mapCenter = Vec2(FARMYARD_MAP_WIDTH * MAP_TILE_WIDTH / 2, FARMYARD_MAP_HEIGHT * MAP_TILE_HEIGHT / 2);

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

	// ��ȡ������� x �� y ����
	float spawnX = spawnPoint["x"].asFloat();
	float spawnY = spawnPoint["y"].asFloat();
	CCLOG("Spawn point coordinates: (%f, %f)", spawnX, spawnY);

	auto player = Player::getInstance();
	this->addChild(player, 1, "player");
	player->setPosition(spawnX, spawnY);
	player->setCameraMask(unsigned short(CameraFlag::USER1));

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

Vec2 FarmYardScene::convertToTileCoords(const Vec2& pos)
{
	// ����ҵ���λ��ת��Ϊ��Ƭ����
	Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH), int((FARMYARD_MAP_HEIGHT * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

	return tile;
}

void FarmYardScene::registerMouseScrollListener()
{
	// ��������¼�������
	auto listener = EventListenerMouse::create();
	listener->onMouseScroll = CC_CALLBACK_1(FarmYardScene::onMouseScroll, this);

	// ��ȡ�¼��ַ�������Ӽ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// �������¼��ص�
void FarmYardScene::onMouseScroll(cocos2d::EventMouse* event)
{
	auto scrollDelta = event->getScrollY(); // ��ȡ��������
	CCLOG("Mouse Scroll Delta: %f", scrollDelta);
	// �����������λ��
	Vec3 currentCameraPos = _camera->getPosition3D();
	// ��������ͷĿ��λ��
	currentCameraPos.z += 15 * scrollDelta;
	if (currentCameraPos.z > 750.0)currentCameraPos.z = 750.0;
	else if (currentCameraPos.z < 250.0)currentCameraPos.z = 250.0;
	Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
	// ƽ���ƶ������
	_camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f));
}

// ������¼��ص�
void FarmYardScene::onMouseClick(cocos2d::EventMouse::MouseButton mouseButton)
{
	Player* player = Player::getInstance();
	InputManager* inputManager = InputManager::getInstance();

	// ��ȡ FarmYard ��ͼ����
	auto FarmYard = (TMXTiledMap*)this->getChildByName("FarmYard");

	// ��ȡ��Ƭͼ��
	auto tileLayer = FarmYard->getLayer("Meta");
	auto groundLayer = FarmYard->getLayer("Ground");
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

	// ������Һ����֮�����Ƭ����
	float distance = sqrt(pow(currenttile.x - mousetile.x, 2) + pow(currenttile.y - mousetile.y, 2));

	// �ж�������İ�ť
	if (mouseButton == EventMouse::MouseButton::BUTTON_LEFT) {
		CCLOG("Left mouse button clicked at: (%f, %f)", mousetile.x, mousetile.y);
		// ִ����������ز���
	}
	else if (mouseButton == EventMouse::MouseButton::BUTTON_RIGHT) {
		CCLOG("Right mouse button clicked at: (%f, %f)", mousetile.x, mousetile.y);
		// ִ���Ҽ������ز���
	}

	// �жϾ����Ƿ�С�ڽ�����Χ�����轻����ΧΪ 2��
	if (distance > 2) {
		CCLOG("Too far to interact");
	}
	else {
		// ��ȡ���λ�õ���Ƭ GID
		int mouseGID = tileLayer->getTileGIDAt(mousetile);

		// ��� GID ��Ϊ�գ���ʾ��λ�ÿ��Խ���
		if (mouseGID) {
			// ��ȡ��Ƭ����
			auto properties = FarmYard->getPropertiesForGID(mouseGID).asValueMap();
			if (!properties.empty()) {
				// �ж���Ƭ�Ƿ���� "Plowable" ������Ϊ true
				if (properties["Plowable"].asBool()) {
					// ִ�н�������
					auto Soil = Sprite::create("DrySoil.png");
					Soil->setAnchorPoint(Vec2(0, 0));
					this->addChild(Soil);
					Soil->setPosition(Vec2(mousetile.x * MAP_TILE_WIDTH, (FARMYARD_MAP_HEIGHT - mousetile.y) * MAP_TILE_HEIGHT));
					Soil->setCameraMask(unsigned short(CameraFlag::USER1));
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
	PlayerController::getInstance()->update();
	Player* player = Player::getInstance();

	// ��ȡ FarmYard ��ͼ����
	auto FarmYard = (TMXTiledMap*)this->getChildByName("FarmYard");

	// �����������λ��
	Vec3 currentCameraPos = _camera->getPosition3D();

	// �����ҵĵ�ǰλ�ò�ת��Ϊ��Ƭ����
	Vec2 currentPosition = player->getPosition();
	Vec2 currenttile = convertToTileCoords(currentPosition);

	// ��ȡ��Ƭͼ��
	auto tileLayer = FarmYard->getLayer("Meta");
	if (!tileLayer) {
		CCLOG("Layer not found");
		return;
	}

	// ������º��λ��
	Vec2 newPosition = currentPosition + player->getDirection() * player->getSpeed() * delta;

	// ��ȡ���Ŀ��λ�õ���ƬGID
	int tileGID = tileLayer->getTileGIDAt(convertToTileCoords(newPosition));

	if (tileGID) {
		// ��ȡ��Ƭ����
		auto properties = FarmYard->getPropertiesForGID(tileGID).asValueMap();
		if (!properties.empty()) {
			// �ж���Ƭ�Ƿ���� "Collidable" ������Ϊ true
			if (properties["Collidable"].asBool()) {
				// �������Ƭ����ͨ�У���ֱ�ӷ��أ����������λ��
				return;
			}
		}
	}

	// �������λ��
	player->setPosition(newPosition);

	// ����ʱ����ʾ
	// auto removelabel = this->getChildByName("timelabel");
	// if (removelabel != nullptr) {
	//	removelabel->removeFromParentAndCleanup(true);
	// }
	// auto timeLabel = Label::createWithSystemFont(gametime->toString(), "Arial", 30);
	// timeLabel->setPosition(Vec2(_camera->getPosition3D().x + Director::getInstance()->getVisibleSize().width / 2 - timeLabel->getContentSize().width, _camera->getPosition3D().y + Director::getInstance()->getVisibleSize().height / 2 - timeLabel->getContentSize().height));
	// this->addChild(timeLabel, 10, "timelabel");
	// timeLabel->setCameraMask(unsigned short(CameraFlag::USER1));

	// ��������ͷĿ��λ��
	Vec3 targetCameraPos(newPosition.x, newPosition.y, currentCameraPos.z);

	// ƽ���ƶ������
	_camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f)); // ƽ��ϵ��
}
