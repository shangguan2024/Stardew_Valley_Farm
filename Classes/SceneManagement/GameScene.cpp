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
    tilemap = TMXTiledMap::create(tileMapPath);
    if (!tilemap) {
        CCLOG("Failed to load tile map");
        return false;
    }
    this->addChild(tilemap);
    tilemap->setPosition(0, 0);
    tilemap->setCameraMask(unsigned short(CameraFlag::USER1));

    // ���������
    auto winSize = Director::getInstance()->getWinSize();
    float zeye = Director::getInstance()->getZEye();

    camera = Camera::createPerspective(fov, winSize.width / winSize.height, 10, zeye + winSize.height / 2.0f);
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);
    // ��ʼ��������߶�
    Vec3 currentCameraPos = camera->getPosition3D();
    currentCameraPos.z = CAMERA_Z;
    Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
    camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.0f));

    // ���� Meta Ϊ���ɼ���
    auto tileLayer = tilemap->getLayer("Meta");
    tileLayer->setVisible(false);
    tileLayer->setLocalZOrder(255); 

    // ���س�����
    auto objectGroup = tilemap->getObjectGroup("Event");
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

    // �ڳ����㴴�����
    auto player = Player::getInstance();
    this->addChild(player, 1, "player");
    player->setPosition(spawnX, spawnY);
    player->setCameraMask(unsigned short(CameraFlag::USER1));

    // UI ����
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
    mapName = MapName::Null;
    tileMapPath = "path/to/tilemap.tmx";
}

Vec2 GameScene::convertToTileCoords(const Vec2& pos)
{
    // ����ҵ���λ��ת��Ϊ��Ƭ����
    Size tilemapSize = tilemap->getMapSize();
    Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH), 
                     int((tilemapSize.height * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

    return tile;
}

bool GameScene::setCameraCenter(const Vec3& currentCameraPos)
{
    // ��������ͷĿ��λ�� �� ƽ���ƶ������
    Vec2 leftUpMargin, rightDownMargin, 
        target(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y);

    const auto& mapblock = tilemap->getMapSize();
    const auto& tilesize = tilemap->getTileSize();
    const auto& winSize = Director::getInstance()->getWinSize();
    auto mapsize = Size(mapblock.width * tilesize.width, mapblock.height * tilesize.height);

    // default fov = 60 deg
    const auto& aspect_ratio = winSize.width / winSize.height;
    const auto& fov2z = 2 * currentCameraPos.z * tan(60.0/180 * 3.14 / 2);
    Size visibleSize = Size(fov2z * aspect_ratio, fov2z);
    leftUpMargin = visibleSize / 2;
    rightDownMargin = mapsize - visibleSize / 2;

    if (leftUpMargin.x > rightDownMargin.x || leftUpMargin.y > rightDownMargin.y)
        return false;

    if (target.x < leftUpMargin.x) {
        target.x = leftUpMargin.x;
    } else if (target.x > rightDownMargin.x) {
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
    currentCameraPos.z += 15 * scrollDelta;
    if (!setCameraCenter(currentCameraPos))
        currentCameraPos.z -= 15 * scrollDelta;
    if (currentCameraPos.z < 128.0)
        currentCameraPos.z = 128.0;
    Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
    // ƽ���ƶ������
    camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.8f));
}

// ������¼��ص�
void GameScene::onMouseClick(cocos2d::EventMouse::MouseButton mouseButton)
{
    Player* player = Player::getInstance();
    InputManager* inputManager = InputManager::getInstance();


    // ��ȡ��Ƭͼ��
    auto tileLayer = tilemap->getLayer("Meta");
    auto groundLayer = tilemap->getLayer("Ground");
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
            auto properties = tilemap->getPropertiesForGID(mouseGID).asValueMap();
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


    // ��ȡ��Ƭͼ��
    auto tileLayer = tilemap->getLayer("Meta");
    if (!tileLayer) {
        CCLOG("Layer not found");
        return;
    }

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
        }
        else {
            auto xxx = tilemap->getPropertiesForGID(tileGID).asValueMap();
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
            auto xxx = tilemap->getPropertiesForGID(tileGID).asValueMap();
            if (xxx.find("Collidable") == xxx.end()) {
                player->setPosition(newPosition);
            }
        }
    }
    
    // �����������λ��
    Vec3 currentCameraPos = camera->getPosition3D();
    setCameraCenter(currentCameraPos);
}
