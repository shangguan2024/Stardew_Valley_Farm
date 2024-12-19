/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTimeLayer.h
 * File Function: GameTimeLayer类的定义
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#ifndef _GAME_TIME_LAYER_H_
#define _GAME_TIME_LAYER_H_

#include "cocos2d.h"
#include "../GameTime/GameTime.h"

class GameTimeLayer :public cocos2d::Layer
{
public:
	// 初始化
	virtual bool init() override;

	// 创建函数
	CREATE_FUNC(GameTimeLayer);
	
	// 更新时间
	void updateTime(float delta);

private:

	// 显示时间的标签
	cocos2d::Label* timeLabel;

	// 显示时间图标的精灵
	cocos2d::Sprite* timeIcon;

};

#endif // _GAME_TIME_LAYER_H_