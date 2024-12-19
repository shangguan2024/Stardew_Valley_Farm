/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Manager.h
 * File Function: Manager类的定义
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#ifndef _MANAGER_
#define _MANAGER_

#include "vector"
#include "cocos2d.h"
#include "Object.h"
#include "FarmLand.h"

class Manager
{
public:
    // 获取单例指针
	static Manager& getInstance();

    // 添加对象
    void addObject(const Object& obj);

    // 添加耕地
    void addFarmland(const FarmLand& land);

    void saveGameState(const std::string& filename);

    void loadGameState(const std::string& filename);

private:
    std::vector<Object> objects;      // 非耕地物体
    std::vector<FarmLand> farmlands;  // 耕地物体

    // 私有构造函数，禁止外部实例化
    Manager();

    // 禁止拷贝和赋值
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    static Manager* instance;

};

#endif // _MANAGER_
