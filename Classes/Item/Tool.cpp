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
	switch (tooltype) {
		case  HOE:
			return TOOL_HOE_DESCRIPTION;
			break;
		case WATERING_CAN:
			return TOOL_WATERING_CAN_DESCRIPTION;
			break;
		case   PICKAXE:
			return TOOL_PICKAXE_DESCRIPTION;
			break;
		case  AXE:
			return TOOL_AXE_DESCRIPTION;
			break;
		case  SCYTHE:
			return TOOL_SCYTHE_DESCRIPTION;
			break;
		case FISHING_ROD:
			return TOOL_FISHING_ROD_DESCRIPTION;
			break;
		default:
			return " ";
			break;
	}
}

