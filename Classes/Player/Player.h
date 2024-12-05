/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Player.h
 * File Function: Player类的定义
 * Author:        上官思杨、李昊、张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Bag.h"
#include "SkillTree.h"
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

    cocos2d::Vec2 _direction; // 玩家移动方向向量
    float _speed;             // 玩家速度

    cocos2d::EventListenerKeyboard* _keyboardListener; // 键盘监听器

    static Player* _instance; // 静态实例指针
};

#endif // _PLAYER_H_
