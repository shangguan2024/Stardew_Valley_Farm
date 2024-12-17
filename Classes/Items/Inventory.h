#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "cocos2d.h"
#include "Item.h"


class Inventory
{
public:
    Inventory();  // 构造函数声明

    Item::id getItemId(int row, int col);  // 获取物品ID声明
    size_t getItemNum(int row, int col);  // 获取物品数量声明

    void click(int row, int col);  // 点击操作声明

    static Inventory* getInstance();  // 获取实例声明

    bool init();  // 初始化声明

private:
    static Item::id backpack[3][12];  // 背包物品ID
    static size_t itemNum[3][12];  // 背包物品数量
    Item::id suspended;  // 挂起物品ID
    size_t suspendedNum;  // 挂起物品数量
};

#endif
