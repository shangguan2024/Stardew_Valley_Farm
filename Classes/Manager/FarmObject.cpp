/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Object.cpp
 * File Function: Object类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "FarmObject.h"

USING_NS_CC;

FarmObject::FarmObject(ObjectType type, float x, float y)
{
	// 设置对象的类型
	objecttype = type;
	// 设置碰撞面积大小
	switch (objecttype){
		case TREE:
			objectsize.setRect(x, y, 16, 16);

			break;
		case WEED:
			objectsize.setRect(x, y, 16, 16);

			break;
		case STONE:
			objectsize.setRect(x, y, 16, 16);

			break;
		case CROP:
			objectsize.setRect(x, y, 16, 16);

			break;
		default:
			break;
	}

	// 设置当前状态为初始状态
	currstate = 1;

	// 成长率设置为初始
	growthrate = 0;
}

FarmObject::~FarmObject(){}

bool FarmObject::ismature()
{
	return currstate == maxstate;
}

void FarmObject::update()
{
	// 如果已经成熟
	if (ismature())
		return;

	// 根据成长速度添加成长率
	growthrate += growthspeed;
	if (growthrate >= 1)
		currstate++;
}
