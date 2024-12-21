/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmObject.cpp
 * File Function: FarmObject类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "FarmObject.h"

USING_NS_CC;

FarmObject::FarmObject(ObjectType type, float x, float y) :sprite(nullptr), currstate(1), growthrate(0), toRemove(false)
{
	// 设置对象的类型
	objecttype = type;
	// 设置碰撞面积大小
	switch (objecttype){
		case TREE:
			objectsize.setRect(x, y, 16, 16);
			sprite = Sprite::create("ImageElements/FarmLands/DrySoil.png");
			break;
		case WEED:
			objectsize.setRect(x, y, 16, 16);
			sprite = Sprite::create("ImageElements/FarmLands/DrySoil.png");
			break;
		case STONE:
			objectsize.setRect(x, y, 16, 16);
			sprite = Sprite::create("ImageElements/FarmLands/DrySoil.png");
			break;
		case CROP:
			objectsize.setRect(x, y, 16, 16);
			sprite = Sprite::create("ImageElements/FarmLands/DrySoil.png");
			break;
		default:
			break;
	}
	if (sprite != nullptr) {
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(x, y);
	}
}

FarmObject::~FarmObject(){}

void FarmObject::update()
{
	// 如果已经成熟
	if (ismature())
		return;

	// 根据成长速度添加成长率
	growthrate += growthspeed;
	if (growthrate >= 1) {
		currstate++;
		growthrate = 0;
	}
}

bool FarmObject::ismature()
{
	return currstate == maxstate;
}

bool FarmObject::shouldRemove() const
{
	return toRemove;
}

void FarmObject::markForRemoval()
{
	toRemove = true;
}

Sprite* FarmObject::getSprite() const
{
	return sprite;
}

ObjectType FarmObject::getObjectType() const
{
	return objecttype;
}

void FarmObject::setCurrState(int state)
{
	currstate = state;
}

int FarmObject::getCurrState() const
{
	return currstate;
}
