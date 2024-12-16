#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "proj.win32/Constant.h"
#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
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

    // ע����̼�����
    void registerKeyboardListener();

    // ����ʵ��
    static void destroyInstance();

    // �����ٶ�
    void setSpeed(const float speed);
    float getSpeed() const;

private:
    Player();  // ���캯��˽�л�
    ~Player(); // ��������˽�л�

    // ��ֹ�����͸�ֵ
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    cocos2d::Vec2 _direction;     // ����ƶ���������
    float _speed;                 // ����ٶ�
    size_t _currentAnimationHash; // ��ǰ���ŵĶ���

    cocos2d::EventListenerKeyboard* _keyboardListener; // ���̼�����

    static Player* _instance; // ��̬ʵ��ָ��
};

#endif
