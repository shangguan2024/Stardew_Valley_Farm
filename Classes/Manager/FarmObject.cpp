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
	objecttype = type;

	objectsize.setRect(x, y, 16, 16);
	currstate = 0;
}

FarmObject::~FarmObject(){}