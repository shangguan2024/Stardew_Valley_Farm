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

Manager::Manager() {}

Manager* Manager::getInstance()
{
    if (instance == nullptr) {
        instance = new(std::nothrow)Manager();
        if (!instance || !instance->init()) {
           
        }
    }
	return instance;
}

bool Manager::init()
{

    return true;
}

void Manager::addToScene(Scene* scene)
{
    for (auto& land : lands) {
        if (land.getSprite()) {
            scene->addChild(land.getSprite(), 1);
            land.getSprite()->setCameraMask(unsigned short(CameraFlag::USER1));
        }
    }
    for (auto& obj : objects) {
        if (obj.getSprite()) {
            scene->addChild(obj.getSprite(), 2);
            obj.getSprite()->setCameraMask(unsigned short(CameraFlag::USER1));
        }
    }
}

void Manager::addObject(const FarmObject& obj, Scene* scene)
{
	objects.push_back(obj);
    if (obj.getSprite()) {
        scene->addChild(obj.getSprite());
        obj.getSprite()->setCameraMask(unsigned short(CameraFlag::USER1));
    }
}

void Manager::addFarmland(const FarmLand& land, Scene* scene)
{
	lands.push_back(land);
    if (land.getSprite()) {
        scene->addChild(land.getSprite());
        land.getSprite()->setCameraMask(unsigned short(CameraFlag::USER1));
    }
}

void Manager::update()
{
    // 更新耕地
    for (auto it = lands.begin(); it != lands.end(); ) {
        if (it->shouldRemove()) {
            // 从场景中移除精灵
            it->getSprite()->removeFromParent();
            it = lands.erase(it);
        }
        else {
            it->update();
            it++;
        }
    }

    // 更新非耕地实体
    for (auto it = objects.begin(); it != objects.end(); ) {
        if (it->shouldRemove()) {
            // 从场景中移除精灵
            it->getSprite()->removeFromParent();
            it = objects.erase(it);
        }
        else {
            it->update();
            it++;
        }
    }
}

void Manager::saveGameState(const std::string& filename)
{

}

void  Manager::loadGameState(const std::string& filename)
{

}