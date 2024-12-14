/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Tool.cpp
 * File Function: Tool类的实现
 * Author:        张翔
 * Update Date:   2024/12/14
 ****************************************************************/

#include "Tool.h"

Tool::Tool(const ToolType _tooltype, std::string _image, int _maxstack, int _price)
	:Item(ItemType::TOOL, _image, _maxstack, _price), tooltype(_tooltype) {
}

std::string Tool::getDescription() const
{
	if (tooltype == HOE)
		return TOOL_HOE_DESCRIPTION;
	else if(tooltype == WATERING_CAN)
		return TOOL_WATERING_CAN_DESCRIPTION;
	else if (tooltype == PICKAXE)
		return TOOL_PICKAXE_DESCRIPTION;
	else if (tooltype == AXE)
		return TOOL_AXE_DESCRIPTION;
	else if (tooltype == SCYTHE)
		return TOOL_SCYTHE_DESCRIPTION;
	else if (tooltype == FISHING_ROD)
		return TOOL_FISHING_ROD_DESCRIPTION;
}

