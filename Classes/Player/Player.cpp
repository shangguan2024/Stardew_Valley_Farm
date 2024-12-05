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
        if (_instance && !_instance->init()) {   
            CC_SAFE_DELETE(_instance);
        }
    }
    return _instance;
}

// 构造函数
Player::Player() : _direction(Vec2::ZERO), _keyboardListener(nullptr) , _speed(NOMAL_PLAYER_SPEED){}

// 析构函数
Player::~Player()
{
    if (_keyboardListener) {
        // 检查监听器是否还在事件调度器中
        _eventDispatcher->removeEventListener(_keyboardListener);
        _keyboardListener = nullptr; // 避免悬空指针
    }
    // 调用父类的析构函数以释放 Sprite 资源
    Sprite::~Sprite();
}

// 初始化
bool Player::init() 
{
    if (!Sprite::init()) {
        return false;
    }

    // 加载玩家纹理
    if (!this->initWithFile("Dwarf.png")) {
        CCLOG("Failed to load player sprite");
        return false;
    }

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

// 每帧更新
void Player::update(float delta) 
{
    
}

void Player::registerKeyboardListener()
{
    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_W: 
                _direction.y = 1;
                break;
            case EventKeyboard::KeyCode::KEY_S:
                _direction.y = -1; 
                break;
            case EventKeyboard::KeyCode::KEY_A: 
                _direction.x = -1; 
                break;
            case EventKeyboard::KeyCode::KEY_D: 
                _direction.x = 1;
                break;
            default: 
                break;
        }
        };

    eventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
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

    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

// 销毁实例
void Player::destroyInstance() 
{
    CC_SAFE_DELETE(_instance);
}
