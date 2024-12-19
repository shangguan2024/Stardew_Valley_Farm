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

    // ���������
    _camera = Camera::create();
    _camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(_camera);

    // ������Ƭ��ͼ
    auto FarmYard = TMXTiledMap::create(tileMapPath);
    if (!FarmYard) {
        CCLOG("Failed to load tile map");
        return false;
    }

    auto tileLayer = FarmYard->getLayer("Meta");
    tileLayer->setVisible(false);
    tileLayer->setLocalZOrder(255); 

    this->addChild(FarmYard, 0, sceneName);
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

void GameScene::initConstants()
{
    sceneName = "name of this scene";
    tileMapPath = "path/to/tilemap.tmx";
}

Vec2 GameScene::convertToTileCoords(const Vec2& pos)
{
    // ����ҵ���λ��ת��Ϊ��Ƭ����
    Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH), int((50 * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

    return tile;
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
void GameScene::onMouseClick(cocos2d::EventMouse::MouseButton mouseButton)
{
    Player* player = Player::getInstance();
    InputManager* inputManager = InputManager::getInstance();

    // ��ȡ��ͼ����
    auto tileMap = (TMXTiledMap*)this->getChildByName(sceneName);

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
            auto properties = tileMap->getPropertiesForGID(mouseGID).asValueMap();
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

void GameScene::update(float delta)
{
    PlayerController::getInstance()->update();
    Player* player = Player::getInstance();

    // ��ȡ FarmYard ��ͼ����
    auto tileMap = (TMXTiledMap*)this->getChildByName(sceneName);

    // �����������λ��
    Vec3 currentCameraPos = _camera->getPosition3D();

    // ��ȡ��Ƭͼ��
    auto tileLayer = tileMap->getLayer("Meta");
    if (!tileLayer) {
        CCLOG("Layer not found");
        return;
    }


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
        }
        else {
            auto xxx = tileMap->getPropertiesForGID(tileGID).asValueMap();
            if (xxx.find(TILE_COLLIDABLE) == xxx.end()) {
                player->setPosition(newPosition);
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
        }
        else {
            auto xxx = tileMap->getPropertiesForGID(tileGID).asValueMap();
            if (xxx.find("Collidable") == xxx.end()) {
                player->setPosition(newPosition);
            }
        }
    }


    // ��������ͷĿ��λ��
    Vec3 targetCameraPos(player->getPosition().x, player->getPosition().y, currentCameraPos.z);

    // ƽ���ƶ������
    _camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 1.0f)); // ƽ��ϵ��
}
