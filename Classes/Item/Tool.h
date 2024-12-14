/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Tool.h
 * File Function: Tool类的定义
 * Author:        张翔
 * Update Date:   2024/12/14
 ****************************************************************/

#ifndef _TOOL_H_
#define _TOOL_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "Item.h"

class Tool :public Item
{
public:
	// 构造函数
	Tool(const ToolType _type, std::string _image, int _maxstack, int _price);

	std::string getDescription() const override;

private:
	// 工具种类
	ToolType tooltype;



};

#endif // _TOOL_H_
