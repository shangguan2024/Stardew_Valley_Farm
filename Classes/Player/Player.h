#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "proj.win32/Constant.h"
#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
public:
    // 获取单例实例
    static Player* getInstance();

    // 初始化
    virtual bool init() override;

    // 设置方向
    void setDirection(const cocos2d::Vec2& direction);
    cocos2d::Vec2 getDirection() const;

    // 每帧更新
    virtual void update(float delta) override;

    // 注册键盘监听器
    void registerKeyboardListener();

    // 销毁实例
    static void destroyInstance();

    // 设置速度
    void setSpeed(const float speed);
    float getSpeed() const;

private:
    Player();  // 构造函数私有化
    ~Player(); // 析构函数私有化

    // 禁止拷贝和赋值
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    cocos2d::Vec2 _direction;     // 玩家移动方向向量
    float _speed;                 // 玩家速度
    size_t _currentAnimationHash; // 当前播放的动画

    cocos2d::EventListenerKeyboard* _keyboardListener; // 键盘监听器

    static Player* _instance; // 静态实例指针
};

#endif
