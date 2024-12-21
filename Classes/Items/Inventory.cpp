#include "Inventory.h"

// 静态成员初始化
Inventory* Inventory::instance = nullptr;
Inventory::Slot Inventory::inventory[3][12] = {};

Inventory::Inventory()
	: attached(), // 初始化挂起物品为NIL，数量为0
	lastClickRow(-1),
	lastClickCol(-1)
{
}

Inventory::~Inventory()
{
}

Inventory* Inventory::getInstance()
{
	if (!instance) {
		instance = new Inventory();
		if (!instance || !instance->init()) {
			return nullptr;
		}
	}
	return instance;
}

Inventory::Slot Inventory::getSlot(int row, int col)
{
	return inventory[row][col];
}

void Inventory::click(int row, int col)
{
	if (attached == Item::NIL) {
		if (inventory[row][col] != Item::NIL) {
			attached = inventory[row][col];
			inventory[row][col] = Slot();
		}
	}
	else {
		if (inventory[row][col] == Item::NIL) {
			inventory[row][col] = attached;
			attached = Slot();
		}
		else if (inventory[row][col] == attached) {
			merge(row, col, attached.num);
			attached = Slot();
		}
		else if (inventory[row][col] != Item::NIL) {
			std::swap(attached, inventory[row][col]);
		}
	}
	lastClickRow = row;
	lastClickCol = col;

}

bool Inventory::detach()
{
	if (attached != Item::NIL) {
		if (pick(attached)) {
			attached = Slot();
			return true;
		}
		else {
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 11; ++j)
					if (inventory[i][j] == Item::NIL) {
						std::swap(attached, inventory[i][j]);
						return true;
					}
		}
	}
	return false;
}

void Inventory::merge(int row, int col, int num)
{
	inventory[row][col].num += num;
}

Inventory::Slot Inventory::getAttached()
{
	return attached;
}

bool Inventory::pick(const Slot& discarded)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (inventory[i][j] == discarded /* && item.stackable */) {
				merge(i, j, discarded.num);
				return true;
			}
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (inventory[i][j] == Item::NIL) {
				inventory[i][j] = discarded;
				return true;
			}
		}
	}

	return false;
}


bool Inventory::init()
{
	// 在此可以进行初始化操作
	inventory[0][0] = Slot(1, 2);
	inventory[0][1] = Slot(2, 1);
	inventory[0][2] = Slot(2, 1);
	inventory[0][3] = Slot(2, 2);
	inventory[0][4] = Slot(3, 2);
	inventory[0][5] = Slot(4, 2);
	inventory[0][6] = Slot(5, 2);
	inventory[0][7] = Slot(6, 2);
	return true;
}