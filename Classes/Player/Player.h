#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "InputControl/InputManager.h"

class Player : public cocos2d::Sprite {
public:
	// ��ȡ����ʵ��
	static Player* getInstance();

	// ��ʼ��
	virtual bool init() override;

	// ���÷���
	void setDirection(const cocos2d::Vec2& direction);
	cocos2d::Vec2 getDirection() const;

	// ÿ֡����
	virtual void update(float delta) override;

	// ����ʵ��
	static void destroyInstance();

	// �����ٶ�
	void setSpeed(const float speed);
	float getSpeed() const;

	// strength
	void setStrength(const int strength = PLAYER_MAX_STRENGTH);
	int getEnergy() const;
	void addStrength(const int strength);

private:
	Player();  // ���캯��˽�л�
	~Player(); // ��������˽�л�

	// ��ֹ�����͸�ֵ
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	static Player* _instance; // ��̬ʵ��ָ��

	cocos2d::Vec2 _direction;     // ����ƶ���������
	float _speed;                 // ����ٶ�
	size_t _currentAnimationHash; // ��ǰ���ŵĶ���

	int _strength;
};

#endif
