/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Bag.cpp
 * File Function: Bag类的实现
 * Author:        张翔
 * Update Date:   2024/12/7
 ****************************************************************/

#include "Bag.h"
#include "proj.win32/Constant.h"

 // 静态成员变量初始化
Bag* Bag::instance = nullptr;

// 私有构造函数
Bag::Bag(int capacity) : capacity(capacity), currentItemCount(0) {}

// 析构函数
Bag::~Bag()
{
    for (auto item : items)
    {
        delete item; // 释放物品的内存
    }
    items.clear();
    itemCounts.clear();
}

// 获取单例实例
Bag* Bag::getInstance()
{
    if (!instance)
    {
        instance = new Bag(DEFAULT_CAPACITY);
    }
    return instance;
}

// 添加物品到背包
bool Bag::addItem(Item* item, int quantity)
{
    if (currentItemCount >= capacity)
    {
        CCLOG("Bag is full! Cannot add item.");
        return false;
    }

    auto it = itemCounts.find(item->getName());
    if (it != itemCounts.end())
    {
        it->second += quantity; // 更新物品数量
    }
    else
    {
        items.push_back(item);
        itemCounts[item->getName()] = quantity;
        currentItemCount++;
    }
    return true;
}

// 移除物品
bool Bag::removeItem(const std::string& itemName, int quantity)
{
    auto it = itemCounts.find(itemName);
    if (it == itemCounts.end())
    {
        CCLOG("Item not found in the bag.");
        return false;
    }

    if (it->second < quantity)
    {
        CCLOG("Not enough items to remove.");
        return false;
    }

    it->second -= quantity;
    if (it->second == 0)
    {
        // 移除物品
        int index = findItemIndex(itemName);
        if (index != -1)
        {
            delete items[index]; // 释放内存
            items.erase(items.begin() + index);
        }
        itemCounts.erase(it);
        currentItemCount--;
    }
    return true;
}

// 查询物品
Item* Bag::findItem(const std::string& itemName) const
{
    int index = findItemIndex(itemName);
    if (index != -1)
    {
        return items[index];
    }
    return nullptr;
}

// 获得背包的容量
int Bag::getCapacity() const
{
    return capacity;
}

// 获得当前背包中物品的种类数量
int Bag::getCurrentItemCount() const
{
    return currentItemCount;
}

// 查找物品索引
int Bag::findItemIndex(const std::string& itemName) const
{
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (items[i]->getName() == itemName)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}