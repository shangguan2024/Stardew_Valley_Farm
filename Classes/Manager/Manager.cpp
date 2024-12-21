/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Manager.cpp
 * File Function: Manager类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "Manager.h"
#include "proj.win32/Json.hpp"
#include <fstream>

using json = nlohmann::json;

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

FarmLand* Manager::findFarmlandByPosition(float x, float y)
{
    for (auto& land : lands) {
        // 检查耕地的中心坐标是否匹配
        auto pos = land.getSprite()->getPosition();
        if (std::abs(pos.x - x) < 0.01 && std::abs(pos.y - y) < 0.01) {
            return &land;
        }
    }
    return nullptr; 
}

FarmObject* Manager::findObjectByPosition(float x, float y)
{
    for (auto& obj : objects) {
        // 检查对象的中心坐标是否匹配
        auto pos = obj.getSprite()->getPosition();
        if (std::abs(pos.x - x) < 0.01 && std::abs(pos.y - y) < 0.01) {
            return &obj;
        }
    }
    return nullptr; 
}

void Manager::update()
{
    CCLOG("Manager update called");
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
    // 创建一个 JSON 对象用于存储所有数据
    json gameData;

    // 保存耕地数据
    json landsData = json::array();
    for (const auto& land : lands) {
        json landJson;
        landJson["x"] = land.getSprite()->getPositionX();
        landJson["y"] = land.getSprite()->getPositionY();
        landJson["state"] = static_cast<int>(land.getLandState());
        landsData.push_back(landJson);
    }
    gameData["lands"] = landsData;

    // 保存非耕地对象数据
    json objectsData = json::array();
    for (const auto& obj : objects) {
        json objJson;
        objJson["x"] = obj.getSprite()->getPositionX();
        objJson["y"] = obj.getSprite()->getPositionY();
        objJson["type"] = static_cast<int>(obj.getObjectType());
        objJson["currstate"] = obj.getCurrState();
        objectsData.push_back(objJson);
    }
    gameData["objects"] = objectsData;

    // 写入到文件
    std::ofstream file(filename);
    if (file.is_open()) {
        file << gameData.dump(4);  // 以缩进格式保存
        file.close();
    }
}

void  Manager::loadGameState(const std::string& filename)
{
    // 打开文件并读取 JSON 数据
    std::ifstream file(filename);
    if (!file.is_open()) {
        CCLOG("无法打开文件: %s", filename.c_str());
        return;
    }

    json gameData;
    file >> gameData;
    file.close();

    // 清空当前数据
    lands.clear();
    objects.clear();

    // 加载耕地数据
    for (const auto& landJson : gameData["lands"]) {
        float x = landJson["x"];
        float y = landJson["y"];
        LandState state = static_cast<LandState>(landJson["state"]);
        FarmLand land(x, y);
        land.setLandState(state);
        lands.push_back(land);
    }

    // 加载非耕地对象数据
    for (const auto& objJson : gameData["objects"]) {
        float x = objJson["x"];
        float y = objJson["y"];
        ObjectType type = static_cast<ObjectType>(objJson["type"]);
        int currstate = objJson["currstate"];
        FarmObject obj(type, x, y);
        obj.setCurrState(currstate);
        objects.push_back(obj);
    }
}
