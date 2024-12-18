/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Player.cpp
 * File Function: Player类的实现
 * Author:        张翔、上官思杨、李昊
 * Update Date:   2024/12/5
 ****************************************************************/

#include "Player.h"

USING_NS_CC;

// 静态实例初始化
Player* Player::_instance = nullptr;

// 获取单例实例
Player* Player::getInstance() 
{
    if (_instance == nullptr) {
        // 使用 no-throw 分配内存
        _instance = new (std::nothrow) Player(); 
        // 初始化失败则销毁实例
        if (!_instance || !_instance->init()) {   
            CC_SAFE_DELETE(_instance);
        }
    }
    return _instance;
}

// 构造函数
Player::Player() : _direction(Vec2::ZERO), _faceto(Vec2::ZERO), _keyboardListener(nullptr), _speed(NOMAL_PLAYER_SPEED), _currentAnimationHash(0), isinit(false) {}

// 析构函数
Player::~Player()
{
    if (_keyboardListener) {
        // 检查监听器是否还在事件调度器中
        _eventDispatcher->removeEventListener(_keyboardListener);
        _keyboardListener = nullptr; // 避免悬空指针
    }

    // 清除人物移动动画缓存
    AnimationCache::getInstance()->removeAnimation("WALK_DOWN");
    AnimationCache::getInstance()->removeAnimation("WALK_RIGHT");
    AnimationCache::getInstance()->removeAnimation("WALK_UP");
    AnimationCache::getInstance()->removeAnimation("WALK_LEFT");
    
    // 调用父类的析构函数以释放 Sprite 资源
    Sprite::~Sprite();
}

// 初始化
bool Player::init() 
{
    // 根据是否初始化来判断是否要重新加载动画
    if (isinit) {
        return true;
    }
    isinit = true;

    if (!Sprite::init()) {
        return false;
    }

    // 初始化动画缓存
    auto texture = Director::getInstance()->getTextureCache()->addImage("Player/Sandy.png");

    // 裁剪初始图像
    Rect rect(0, PLAYER_IMAGE_HEIGHT - PLAYER_FRAME_HEIGHT, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT);

    // 创建裁剪出来的精灵帧
    auto frame = SpriteFrame::createWithTexture(texture, rect);

    if (frame) {
        // 设置精灵的初始图像为裁剪出来的部分
        this->setSpriteFrame(frame);
    }
    else {
        CCLOG("Failed to create sprite from the specified rect");
        return false;
    }

    // 设置锚点到脚的中间位置
    this->setAnchorPoint(Vec2(0.5f, 0.0f));

    // 按方向创建动画
    for (int row = 0; row < PLAYER_DIRECTION_NUM; row++) {
        Vector<SpriteFrame*> frames;
        for (int col = 0; col < PLAYER_FRAME_RATE; col++) {
            int x = col * PLAYER_FRAME_WIDTH;
            int y = row * PLAYER_FRAME_HEIGHT;
            auto frame = SpriteFrame::createWithTexture(texture, Rect(x, y, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT));
            frames.pushBack(frame);
        }

        // 设置动画键
        std::string key;
        switch (row) {
            case 0:
                key = "WALK_DOWN";
                break;
            case 1:
                key = "WALK_RIGHT";
                break;
            case 2:
                key = "WALK_UP";
                break;
            case 3:
                key = "WALK_LEFT";
                break;
        }

        // 缓存动画
        auto animation = Animation::createWithSpriteFrames(frames, PLAYER_FRAME_DELAY);
        AnimationCache::getInstance()->addAnimation(animation, key);
    }

    // 重置速度和方向
    _direction = _faceto = Vec2::ZERO;

    // 注册 update
    this->scheduleUpdate();

    // 注册键盘监听器
    registerKeyboardListener();

    return true;

}

// 设置方向
void Player::setDirection(const Vec2& direction) 
{
    // 保证方向向量归一化
    _direction = direction.getNormalized(); 
}

// 获取方向
Vec2 Player::getDirection() const 
{
    return _direction;
}

Vec2 Player::getFaceto() const
{
    return _faceto;
}

// 设置速度
void Player::setSpeed(const float speed)
{
    _speed = speed;
}

// 获取速度
float Player::getSpeed() const
{
    return _speed;
}

void Player::resetInit() 
{
    isinit = false;
}

// 每帧更新
void Player::update(float delta) 
{
    // 如果没有方向输入，停止动画
    if (_direction.isZero()) {
        this->stopActionByTag(_currentAnimationHash); // 使用当前动画的哈希值来停止动画
        _currentAnimationHash = 0;
        return;
    }

    // 判断当前的方向并设置动画关键字
    std::string animationKey;
    if (_direction.y > 0) {
        animationKey = "WALK_UP";   // 向上
    }
    else if (_direction.y < 0) {
        animationKey = "WALK_DOWN"; // 向下
    }
    else if (_direction.x < 0) {
        animationKey = "WALK_LEFT"; // 向左
    }
    else if (_direction.x > 0) {
        animationKey = "WALK_RIGHT"; // 向右
    }

    // 获取动画的哈希值，用于判断是否重复播放
    size_t animationHash = std::hash<std::string>()(animationKey);

    // 如果当前正在播放目标动画，直接返回
    if (_currentAnimationHash == animationHash) {
        return; 
    }

    // 停止当前动画
    this->stopActionByTag(_currentAnimationHash); 
    auto animation = AnimationCache::getInstance()->getAnimation(animationKey);
    if (animation) {
        auto animate = Animate::create(animation);
        auto repeat = RepeatForever::create(animate);
        // 使用动画哈希值作为tag
        repeat->setTag(animationHash); 
        this->runAction(repeat);
        // 更新当前动画哈希值
        _currentAnimationHash = animationHash; 
    }
}

void Player::registerKeyboardListener()
{
    if (_keyboardListener != nullptr)
        return;

    // 创建新的键盘事件监听器
    _keyboardListener = EventListenerKeyboard::create();

    _keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_W:
                _direction = _faceto = Vec2(0, 1); // 向上移动
                break;
            case EventKeyboard::KeyCode::KEY_S:
                _direction = _faceto = Vec2(0, -1); // 向下移动
                break;
            case EventKeyboard::KeyCode::KEY_A:
                _direction = _faceto = Vec2(-1, 0); // 向左移动
                break;
            case EventKeyboard::KeyCode::KEY_D:
                _direction = _faceto = Vec2(1, 0); // 向右移动
                break;
            default:
                break;
        }
        };

    _keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        // 当按键松开时，停止对应方向的移动
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_W:
                if (_direction.y == 1)
                    _direction.y = 0;
                break;
            case EventKeyboard::KeyCode::KEY_S:
                if (_direction.y == -1)
                    _direction.y = 0;
                break;
            case EventKeyboard::KeyCode::KEY_A:
                if (_direction.x == -1)
                    _direction.x = 0;
                break;
            case EventKeyboard::KeyCode::KEY_D:
                if (_direction.x == 1)
                    _direction.x = 0;
                break;
            default:
                break;
        }
        };

    // 将监听器添加到事件调度器中，并绑定到 Player 节点
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}

void Player::removeKeyboardListener()
{
    if (_keyboardListener) {
        _eventDispatcher->removeEventListener(_keyboardListener); // 移除监听器
        _keyboardListener = nullptr;  // 释放监听器
    }
}

// 销毁实例
void Player::destroyInstance() 
{
    CC_SAFE_DELETE(_instance);
}
