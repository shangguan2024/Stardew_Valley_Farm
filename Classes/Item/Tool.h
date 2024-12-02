/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Tool.h
 * File Function: Tool类的定义
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef _TOOL_H_
#define _TOOL_H_

#include "cocos2d.h"
#include <string>

class Tool : public cocos2d::Ref
{
public:
    // 工具类型的枚举
    enum class ToolType {
        HOE,       // 锄头
        AXE,       // 斧头
        WATER_CAN  // 水桶
        // 不全 自己补充
    };

    // 构造函数
    static Tool* create(ToolType type, int level);

    // 使用工具
    bool useTool();

    // 升级工具
    void upgrade();

    // 获取工具属性
    ToolType getType() const { return type; }
    int getLevel() const { return level; }

private:

    ToolType type;
    int level;
};

#endif // _TOOL_H_
