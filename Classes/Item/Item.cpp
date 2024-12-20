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

const ItemType& Item::getType()
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
