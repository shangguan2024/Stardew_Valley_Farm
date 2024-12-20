/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Manager.cpp
 * File Function: Manager类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "Manager.h"

USING_NS_CC;

Manager* Manager::instance = nullptr;

Manager* Manager::getInstance()
{
	return instance;
}

void Manager::addObject(const FarmObject& obj)
{

}

void Manager::addFarmland(const FarmLand& land)
{

}

void Manager::saveGameState(const std::string& filename)
{

}

void  Manager::loadGameState(const std::string& filename)
{

}