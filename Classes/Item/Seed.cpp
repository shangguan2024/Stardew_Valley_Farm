/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Seed.cpp
 * File Function: Seed类的实现
 * Author:        张翔
 * Update Date:   2024/12/14
 ****************************************************************/

#include "Seed.h"

Seed::Seed(const SeedType _seedtype, std::string _image, int _maxstack, int _price)
	:Item(ItemType::SEED, _image, _maxstack, _price), seedtype(_seedtype) {
}

const std::string Seed::getDescription()
{
	switch (seedtype) {
		case  RADISH_SEED:
			return SEED_RADISH_DESCRIPTION;
			break;
		case POTATO_SEED:
			return SEED_POTATO_DESCRIPTION;
			break;
		case  WHEAT_SEED:
			return SEED_WHEAT_DESCRIPTION;
			break;
		default:
			return " ";
			break;
	}
}

const SeedType& Seed::getSubType() 
{
	return seedtype;
}
