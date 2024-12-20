/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Object.h
 * File Function: Object类的定义
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#ifndef _FARMOBJECT_
#define _FARMOBJECT_

#include "cocos2d.h"
#include "FarmObject.h"
#include "../Item/Item.h"
#include "proj.win32/Constant.h"
#include "vector"

class FarmObject
{
public:
	// 对象的种类
	ObjectType objecttype;

	// 对象的碰撞体积
	cocos2d::Rect objectsize;

	// 当前阶段
	int currstate;

private:
	// 最大阶段
	int maxstate;

    // 产量
	std::vector<Item> harvests;

};

#endif // _FARMOBJECT_
