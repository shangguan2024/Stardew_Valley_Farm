/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Inventory.cpp
 * File Function: Inventory类的实现
 * Author:        张翔
 * Update Date:   2024/12/7
 ****************************************************************/

#include "Inventory.h"
#include "proj.win32/Constant.h"

Inventory* Inventory::instance = nullptr;

Inventory::Inventory() {}

Inventory* Inventory::getInstance() 
{
	if (instance == nullptr) {
		instance = new(std::nothrow)Inventory();
		instance->init(DEFAULT_CAPACITY);
		if (!instance) {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

void Inventory::init(int slotCount)
{
	slots.resize(slotCount);
}

int Inventory::findItem(std::shared_ptr<Item> item)
{
	for (int i = 0; i < slots.size(); ++i){
		if (!slots[i].isEmpty() && slots[i].getItem()->getType() == item->getType()){
			// 返回槽位的索引
			return i; 
		}
	}
	return -1;
}

Slot& Inventory::getSlot(int index)
{
	if (index >= 0 && index < slots.size()){
		return slots[index];
	}
	else{
		throw std::out_of_range("Slot index out of range!");
	}
}

void Inventory::changeCurrHeldItem(int change)
{
	currentHeldItemIndex += change;
	// 更新当前所指的手持物
	currentHeldItemIndex %= DEFAULT_BAR;
}

#if 0

bool Inventory::addItem(std::shared_ptr<Item> item, int quantity)
{
	// 先检查背包里有没有这种物品
	// 如果有那么修改数量
	// 如果没有那就新增这个物品
}

bool Inventory::changeItemQuantity(std::shared_ptr<Item> item, int quantity)
{

}

#endif

bool Inventory::swapItems(int index1, int index2)
{
	if (index1 < 0 || index1 >= slots.size() || index2 < 0 || index2 >= slots.size()){
		return false; // 索引越界
	}
	// 交换两个槽位的物品
	std::swap(slots[index1], slots[index2]);
	return true;
}
