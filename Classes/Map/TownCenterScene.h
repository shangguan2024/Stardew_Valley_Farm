/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     TownCenterScene.h
 * File Function: TownCenterScene类的定义
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#include "cocos2d.h"
#include "../NPC/ChatLayer.h"
#include "../NPC/ShopLayer.h"
#include "../NPC/NPC.h"
#include "../Inventory/Inventory.h"
#include "../Inventory/InventoryLayer.h"
class TownCenterScene : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 每一帧被自动调用的 update 方法
    virtual void update(float delta);

    // 鼠标滚动监听器
    void registerMouseScrollListener();
    void onMouseScroll(cocos2d::EventMouse* event);

    // 鼠标点击监听器
    void registerMouseClickListener();
    void onMouseClick(cocos2d::EventMouse* event);

    // 实现 FarmHouseScene 类的 create 方法
    CREATE_FUNC(TownCenterScene);

private:
    // 转变坐标成瓦片坐标
    cocos2d::Vec2 convertToTileCoords(const cocos2d::Vec2& pos);

    // NPC
    NPC* Abigail;
    NPC* Alex;
    NPC* Caroline;
    NPC* Lewis;

    // 定义摄像机
    cocos2d::Camera* camera;

    // 由室内转入农场的判断框
    cocos2d::Rect townToYardRect;

    // 由玩家正在处理的判定框
    cocos2d::Rect targetRect;

};
