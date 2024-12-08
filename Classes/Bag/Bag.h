/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Bag.h
 * File Function: Bag类的定义
 * Author:        张翔
 * Update Date:   2024/12/7
 ****************************************************************/

#ifndef _BAG_H_
#define _BAG_H_

#include "../Item/Item.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "cocos2d.h" // 引入 Cocos2d-x 核心库

class Bag
{
public:
    // 获取单例实例
    static Bag* getInstance();

    // 析构函数
    ~Bag();

    // 禁用拷贝构造和赋值操作符
    Bag(const Bag&) = delete;
    Bag& operator=(const Bag&) = delete;

    // 添加物品到背包
    bool addItem(Item* item, int quantity);

    // 移除物品
    bool removeItem(const std::string& itemName, int quantity);

    // 查询物品
    Item* findItem(const std::string& itemName) const;

    // 获取背包当前状态
    int getCapacity() const;
    int getCurrentItemCount() const;

private:
    // 私有构造函数
    Bag(int capacity);

    // 辅助函数：查找物品索引
    int findItemIndex(const std::string& itemName) const;

    // 属性 
    int capacity;                                     // 背包容量（最大可容纳物品格数）
    int currentItemCount;                             // 当前物品数量
    std::vector<Item*> items;                         // 存储物品的容器
    std::unordered_map<std::string, int> itemCounts;  // 物品名称到堆叠数量的映射

    // 静态单例指针
    static Bag* instance;
};

#endif // _BAG_H_