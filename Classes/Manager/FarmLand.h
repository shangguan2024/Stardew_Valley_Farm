/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmLand.h
 * File Function: FarmLand类的定义
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#ifndef _FARMLAND_
#define _FARMLAND_

#include "cocos2d.h"
#include "FarmObject.h"
#include "proj.win32/Constant.h"

class FarmLand
{
public:
	// 构造函数
	FarmLand(float x, float y);

	// 析构函数
	~FarmLand();

	LandState getState();

	// 更新函数
	void update();

	// 浇水
	void watering();

	// 判断是否需要移除
	bool shouldRemove() const;

	// 设置需要移除
	void markForRemoval();

	cocos2d::Sprite* getSprite() const;

private:
	cocos2d::Sprite* sprite;   // 对应的精灵
	LandState landstate;       // 耕地的状态
	int dryTime;               // 当前干旱时间
	FarmObject* obj;           // 该块耕地上的作物
	bool toRemove;             // 是否要删除

};

#endif // _FARMLAND_
