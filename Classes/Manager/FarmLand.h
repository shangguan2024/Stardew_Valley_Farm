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
#include "FarmLand.h"
#include "FarmObject.h"
#include "proj.win32/Constant.h"

class FarmLand
{
public:
	// 构造函数
	FarmLand(float x, float y);

	// 析构函数
	~FarmLand();

	// 耕地的状态
	LandState landstate;

	// 更新函数
	void update();

	// 浇水
	void watering();

	// 耕地所在位置
	float x, y;

	// 当前干旱时间
	int dryTime;

};

#endif // _FARMLAND_
