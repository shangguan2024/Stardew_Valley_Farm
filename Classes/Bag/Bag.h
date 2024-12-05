/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Bag.h
 * File Function: Bagr类的定义
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef _BAG_H_
#define _BAG_H_

#include "../Item/Item.h"
#include <vector>
#include <unordered_map>
#include <string>

class Bag
{
public:
    // 构造函数
    Bag(int capacity);

    // 添加物品到背包
    bool addItem(Item* item, int quantity);

    // 移除物品
    bool removeItem(const std::string& itemName, int quantity);

    // 查询物品
    Item* findItem(const std::string& itemName) const;

    // 获取背包当前状态
    int getCapacity() const { return capacity; }
    int getCurrentItemCount() const { return currentItemCount; }

private:
    // 辅助函数：查找物品索引
    int findItemIndex(const std::string& itemName) const;

    // 属性
    int capacity;                    // 背包容量（最大可容纳物品格数）
    int currentItemCount;            // 当前物品数量
    std::vector<Item*> items;        // 存储物品的容器
    std::unordered_map<std::string, int> itemCounts; // 物品名称到堆叠数量的映射
};

#endif // _BAG_H_
