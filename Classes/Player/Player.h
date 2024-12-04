/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Player.h
 * File Function: Player类的定义
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Bag.h"
#include "SkillTree.h"
#include "cocos2d.h"

class Player : public cocos2d::Sprite 
{
private:


public:


};
/********
 * PlayerPosition类
 * 用于控制player单位的移动 包括移动 被阻挡 移动速度 移动动画等
*********/
class PlayerPosition :public cocos2d::Sprite
{
private:
    float p_x;              //x坐标
    float p_y;              //y坐标
    float p_x_speed;        //x速度
    float p_y_speed;        //y速度
    float p_x_map;          //所处在地图上的x坐标
    float p_y_map;          //所处在地图上的y坐标
    int p_direction;        //当前人物朝向 1=下 2=左 3=右 4=上
    float timelast = 0;     //帧动画计时
    int p_currentFrame;     //当前帧
    //根据当前帧更新动画
    void updateViewByCurrentFrame();

    //记录当前按键 用于触发操作
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

public:
    PlayerPosition(float pos_x, float pos_y) :p_x(pos_x), p_y(pos_y), p_x_speed(0), p_y_speed(0), p_currentFrame(1) {}
    //构造时需要设置初始坐标
    static PlayerPosition* create(float pos_x, float pos_y);
    virtual bool init();

    //更新 实现移动时的帧动画 改变速度实现移动
    void update(float dt);
    //监测按键是否被按下
    bool IsKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
    //在对应按键被按下时执行对应动作
    void KeyPressedDuration(cocos2d::EventKeyboard::KeyCode keyCode);
};

#endif // _PLAYER_H_
