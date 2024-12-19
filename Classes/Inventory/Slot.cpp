/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Slot.cpp
 * File Function: Slot类的实现
 * Author:        张翔
 * Update Date:   2024/12/7
 ****************************************************************/

#include "Slot.h"

Slot::Slot() : item(nullptr), quantity(0) {}

bool Slot::isEmpty() const
{
	return item == nullptr || quantity == 0;
}

void Slot::setItem(std::shared_ptr<Item> _item, int _quantity)
{
	item = _item;
	quantity = _quantity;
}

void Slot::clearSlot()
{
	item = nullptr;
	quantity = 0;
}

bool Slot::isQuantityEnough(int amount)
{
	return quantity >= amount;
}

void Slot::changeQuantity(int amount)
{
    quantity -= amount;

    // 如果数量变为 0，清空物品
    if (quantity == 0) {
        clearSlot();
    }
}

std::shared_ptr<Item> Slot::getItem() const
{
	return item;
}

int Slot::getQuantity() const
{
	return quantity;
}
