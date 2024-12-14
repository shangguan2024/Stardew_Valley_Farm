/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Inventory.h
 * File Function: Inventory类的定义
 * Author:        张翔
 * Update Date:   2024/12/7
 ****************************************************************/

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "../Item/Item.h"
#include "Slot.h"
#include "cocos2d.h" 

class Inventory
{
public:
	// 获取单例
	static Inventory* getInstance();

	// 禁止拷贝和赋值
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;

	// 初始化背包，设置槽位数
	void init(int slotCount);

	// 检索背包中某件物品的位置
	int findItem(std::shared_ptr<Item> item);

	// 获取背包槽位
	Slot& getSlot(int index);

	// 修改当前手持物
	void changeCurrHeldItem(int change);

	// 添加物品到背包，返回是否成功
	bool addItem(std::shared_ptr<Item> item, int quantity);

	// 修改物品数量
	bool changeItemQuantity(std::shared_ptr<Item> item, int quantity);

	// 交换槽位中的物品
	bool swapItems(int index1, int index2);

private:
	Inventory();

	// 单例指针
	static Inventory* instance;

	// 存储多个槽位
	std::vector<Slot> slots;

	// 当前手持物索引
	int currentHeldItemIndex = 0; 

};

#endif // _INVENTORY_H_