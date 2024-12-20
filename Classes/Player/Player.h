#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "InputControl/InputManager.h"

class Player : public cocos2d::Sprite {
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

	// 销毁实例
	static void destroyInstance();

	PlayerEnterType enterType();
	void setEnterType(const PlayerEnterType& playerEnterType);

	// 设置速度
	void setSpeed(const float speed);
	float getSpeed() const;
	bool isFreeze() const;
	void freeze();
	void unFreeze();

	// strength
	void setStrength(const int strength = PLAYER_MAX_STRENGTH);
	int getEnergy() const;
	void addEnergy(const int strength);

protected:
	void onEnter() override;
	void onExit() override;

private:
	Player();  // 构造函数私有化
	~Player(); // 析构函数私有化

	// 禁止拷贝和赋值
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	static Player* _instance; // 静态实例指针

	size_t _currentAnimationHash; // 当前播放的动画

	PlayerEnterType playerEnterType;
	cocos2d::Vec2 _direction;     // 玩家移动方向向量
	float _speed;                 // 玩家速度
	bool _isFreeze;

	int energy;
};

#endif
