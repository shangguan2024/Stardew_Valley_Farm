#include "Inventory.h"

USING_NS_CC;


// ��̬��Ա��ʼ��
Item::id Inventory::backpack[3][12] = {};
size_t Inventory::itemNum[3][12] = {};

Inventory::Inventory()
    : suspended(Item::NIL), suspendedNum(0) // ��ʼ��������ƷΪNIL������Ϊ0
{
}

Item::id Inventory::getItemId(int row, int col)
{
    return backpack[row][col];
}

size_t Inventory::getItemNum(int row, int col)
{
    return itemNum[row][col];
}

void Inventory::click(int row, int col)
{
    if (suspended == Item::NIL)
    {
        if (backpack[row][col] != Item::NIL)
        {
            suspended = backpack[row][col];
            backpack[row][col] = Item::NIL;

            suspendedNum = itemNum[row][col];
            itemNum[row][col] = 0;
        }
    }
    else
    {
        if (backpack[row][col] == Item::NIL)
        {
            backpack[row][col] = suspended;
            suspended = Item::NIL;

            itemNum[row][col] = suspendedNum;
            suspendedNum = 0;
        }
        else if (backpack[row][col] != Item::NIL)
        {
            std::swap(suspended, backpack[row][col]);
            std::swap(suspendedNum, itemNum[row][col]);
        }
    }
}

Inventory* Inventory::getInstance()
{
    Inventory* ret = new Inventory();
    if (ret && ret->init())
    {
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool Inventory::init()
{
    // �ڴ˿��Խ��г�ʼ������
    return true;
}