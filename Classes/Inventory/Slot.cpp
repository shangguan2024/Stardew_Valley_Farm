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

bool Slot::changeQuantity(int amount)
{
    if (!item || quantity <= 0) {
        CCLOG("Slot is empty or quantity is invalid.");
        return false;
    }

    if (amount <= 0) {
        CCLOG("Reduction amount must be greater than zero.");
        return false;
    }

    if (quantity < amount) {
        CCLOG("Not enough items in the slot to reduce by %d.", amount);
        return false;
    }

    quantity -= amount;

    // 如果数量变为 0，清空物品
    if (quantity == 0) {
        clearSlot();
    }

    return true;
}

std::shared_ptr<Item> Slot::getItem() const
{
	return item;
}

int Slot::getQuantity() const
{
	return quantity;
}
