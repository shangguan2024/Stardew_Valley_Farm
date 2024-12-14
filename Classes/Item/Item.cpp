/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Item.cpp
 * File Function: Item类的实现
 * Author:        张翔
 * Update Date:   2024/12/11
 ****************************************************************/

#include "Item.h"

Item::Item(ItemType _type, std::string _image, int _maxstack, int _price)
	:type(_type), image(_image), maxstack(_maxstack), price(_price) {
}

Item::~Item() {}

std::string Item::getDescription() const
{
	if (this->type == SEED)
		return SEED_DESCRIPTION;
	else if (this->type == TOOL)
		return TOOL_DESCRIPTION;
	else if (this->type == CROP)
		return CROP_DESCRIPTION;
	
}

const ItemType& Item::getType() const
{
	return type;
}

int Item::getMaxStack() const
{
	return maxstack;
}

int Item::getprice() const
{
	return price;
}
