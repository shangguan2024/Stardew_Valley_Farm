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

Item::id Inventory::getItemId(int row, int col)
{
    return inventory[row][col].id;
}

size_t Inventory::getItemNum(int row, int col)
{
    return inventory[row][col].num;
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
        else if (inventory[row][col] != Item::NIL) {
            std::swap(attached, inventory[row][col]);
        }
    }
    lastClickRow = row;
    lastClickCol = col;

}

void Inventory::detach()
{

    if (attached != Item::NIL)
    {
        std::swap(attached, inventory[lastClickRow][lastClickCol]);
    }
}

void Inventory::merge(int row, int col, int num)
{
    inventory[row][col].num += num;
}

bool Inventory::pick(Item::id item, size_t num)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            if (inventory[i][j] == item) //  && item.stackable
            {
                merge(i, j, num);
                return true;
            }
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            if (inventory[i][j] == Item::NIL)
            {
                inventory[i][j] = Slot(item, num);
                return true;
            }
        }
    }

    return false;
}

bool Inventory::init()
{
    // 在此可以进行初始化操作
    inventory[0][0] = Slot(1, 1);
    inventory[0][1] = Slot(2, 1);
    inventory[1][0] = Slot(2, 1);
    inventory[2][0] = Slot(2, 1);
    return true;
}