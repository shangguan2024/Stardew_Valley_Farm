#include "GameScene.h"
#include "InputControl/InputManager.h"
#include "Player/PlayerController.h"
#include "UI/UIManager.h"

USING_NS_CC;

// 初始化场景
bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    initConstants();

    // 加载瓦片地图
    tilemap = TMXTiledMap::create(tileMapPath);
    if (!tilemap) {
        CCLOG("Failed to load tile map");
        return false;
    }
    this->addChild(tilemap);
    tilemap->setPosition(0, 0);
    tilemap->setCameraMask(unsigned short(CameraFlag::USER1));

    // 创建摄像机
    auto winSize = Director::getInstance()->getWinSize();
    float zeye = Director::getInstance()->getZEye();

    camera = Camera::createPerspective(fov, winSize.width / winSize.height, 10, zeye + winSize.height / 2.0f);
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);
    // 初始化摄像机高度
    Vec3 currentCameraPos = camera->getPosition3D();
    currentCameraPos.z = CAMERA_Z;
    Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
    camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.0f));

    // 设置 Meta 为不可见层
    auto tileLayer = tilemap->getLayer("Meta");
    tileLayer->setVisible(false);
    tileLayer->setLocalZOrder(255); 

    // 加载出生点
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
    // 提取出生点的 x 和 y 坐标
    float spawnX = spawnPoint["x"].asFloat();
    float spawnY = spawnPoint["y"].asFloat();
    CCLOG("Spawn point coordinates: (%f, %f)", spawnX, spawnY);

    // 在出生点创建玩家
    auto player = Player::getInstance();
    this->addChild(player, 1, "player");
    player->setPosition(spawnX, spawnY);
    player->setCameraMask(unsigned short(CameraFlag::USER1));

    // UI 调用
    auto camera = Camera::create();
    camera->setCameraFlag(CameraFlag::DEFAULT);
    this->addChild(camera);
    this->addChild(UIManager::getInstance());
    UIManager::getInstance()->setCameraMask(static_cast<unsigned short>(CameraFlag::DEFAULT));

    // 创建并注册鼠标滚轮和鼠标点击事件监听器
    registerMouseScrollListener();
    InputManager::getInstance()->registerMouseCallbackFunc(MouseControlMode::SCENE, [this](cocos2d::EventMouse::MouseButton mouseButton) {
        this->onMouseClick(mouseButton);
        });
    InputManager::getInstance()->setCurrentMouseControlMode(MouseControlMode::SCENE);

    // 启动每帧更新函数
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
    // 将玩家的新位置转换为瓦片坐标
    Size tilemapSize = tilemap->getMapSize();
    Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH), 
                     int((tilemapSize.height * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

    return tile;
}

bool GameScene::setCameraCenter(const Vec3& currentCameraPos)
{
    // 计算摄像头目标位置 并 平滑移动摄像机
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
    camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 1.0f)); // 平滑系数
    return true;
}

void GameScene::registerMouseScrollListener()
{
    // 创建鼠标事件监听器
    auto listener = EventListenerMouse::create();
    listener->onMouseScroll = CC_CALLBACK_1(GameScene::onMouseScroll, this);

    // 获取事件分发器并添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 鼠标滚轮事件回调
void GameScene::onMouseScroll(cocos2d::EventMouse* event)
{
    auto scrollDelta = event->getScrollY(); // 获取滚动增量
    CCLOG("Mouse Scroll Delta: %f", scrollDelta);
    // 计算摄像机的位置
    Vec3 currentCameraPos = camera->getPosition3D();
    // 计算摄像头目标位置
    currentCameraPos.z += 15 * scrollDelta;
    if (!setCameraCenter(currentCameraPos))
        currentCameraPos.z -= 15 * scrollDelta;
    if (currentCameraPos.z < 128.0)
        currentCameraPos.z = 128.0;
    Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z);
    // 平滑移动摄像机
    camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.8f));
}

// 鼠标点击事件回调
void GameScene::onMouseClick(cocos2d::EventMouse::MouseButton mouseButton)
{
    Player* player = Player::getInstance();
    InputManager* inputManager = InputManager::getInstance();


    // 获取瓦片图层
    auto tileLayer = tilemap->getLayer("Meta");
    auto groundLayer = tilemap->getLayer("Ground");
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

    // 计算玩家和鼠标之间的瓦片距离
    float distance = sqrt(pow(currenttile.x - mousetile.x, 2) + pow(currenttile.y - mousetile.y, 2));

    // 判断鼠标点击的按钮
    if (mouseButton == EventMouse::MouseButton::BUTTON_LEFT) {
        CCLOG("Left mouse button clicked at: (%f, %f)", mousetile.x, mousetile.y);
        // 执行左键点击相关操作
    }
    else if (mouseButton == EventMouse::MouseButton::BUTTON_RIGHT) {
        CCLOG("Right mouse button clicked at: (%f, %f)", mousetile.x, mousetile.y);
        // 执行右键点击相关操作
    }

    // 判断距离是否小于交互范围（假设交互范围为 2）
    if (distance > 2) {
        CCLOG("Too far to interact");
    }
    else {
        // 获取鼠标位置的瓦片 GID
        int mouseGID = tileLayer->getTileGIDAt(mousetile);

        // 如果 GID 不为空，表示该位置可以交互
        if (mouseGID) {
            // 获取瓦片属性
            auto properties = tilemap->getPropertiesForGID(mouseGID).asValueMap();
            if (!properties.empty()) {
                // 判断瓦片是否具有 "Plowable" 属性且为 true
                if (properties["Plowable"].asBool()) {
                    // 执行交互操作
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


    // 获取瓦片图层
    auto tileLayer = tilemap->getLayer("Meta");
    if (!tileLayer) {
        CCLOG("Layer not found");
        return;
    }

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
        }
        else {
            auto xxx = tilemap->getPropertiesForGID(tileGID).asValueMap();
            if (xxx.find(TILE_COLLIDABLE) == xxx.end()) {
                player->setPosition(newPosition);
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
        }
        else {
            auto xxx = tilemap->getPropertiesForGID(tileGID).asValueMap();
            if (xxx.find("Collidable") == xxx.end()) {
                player->setPosition(newPosition);
            }
        }
    }
    
    // 计算摄像机的位置
    Vec3 currentCameraPos = camera->getPosition3D();
    setCameraCenter(currentCameraPos);
}
