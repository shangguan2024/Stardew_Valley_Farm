/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     InventoryLayer.h
 * File Function: InventoryLayer类的定义
 * Author:        张翔
 * Update Date:   2024/12/14
 ****************************************************************/

#ifndef _INVENTORY_LAYER_H_
#define _INVENTORY_LAYER_H_
#include "cocos2d.h"
#include "Inventory.h"
#include "Button/HoverButton.h"

class InventoryLayer : public cocos2d::Layer
{
public:
	// 创建一个背包层，初始化背包UI
	static InventoryLayer* create();

	// 初始化
	bool init() override;

	// 关闭背包
	void close();
	
	void open();

	~InventoryLayer() override;
};

#endif //_INVENTORY_LAYER_H_
