/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Item.h
 * File Function: Item类的定义
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef _ITEM_H
#define _ITEM_H

#include "cocos2d.h"
#include <string>

 // 通用 Item 类
class Item : public cocos2d::Ref
{
public:
    enum class ItemType {
        TOOL,        // 工具
        SEED,        // 农作物种子
        // 不全 自己拓展
    };

    // 静态创建方法
    static Item* create(const std::string& name, ItemType type, int value, int stackLimit);

    // 获取物品属性
    std::string getName() const { return name; }
    ItemType getType() const { return type; }
    int getStackLimit() const { return stackLimit; }
    int getCurrentStack() const { return currentStack; }

protected:

    std::string name;       // 物品名称
    ItemType type;          // 物品类型
    int stackLimit;         // 堆叠上限
    int currentStack;       // 当前堆叠数量

};

#endif // _ITEM_H
