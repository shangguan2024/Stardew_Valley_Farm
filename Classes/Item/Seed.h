/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Seed.h
 * File Function: Seed类的定义
 * Author:        张翔
 * Update Date:   2024/12/14
 ****************************************************************/

#ifndef _SEED_H_
#define _SEED_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "Item.h"

class Seed : public Item
{
public:
	// 构造函数
	Seed(const SeedType _seedtype, std::string _image, int _maxstack, int _price);

	std::string getDescription() const override;

private:
	// 种子
	SeedType seedtype;



};

#endif // _SEED_H_
