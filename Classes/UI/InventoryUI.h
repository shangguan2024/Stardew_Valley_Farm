#ifndef __INVENTORY_UI_H__
#define __INVENTORY_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items/Inventory.h"
#include "ResourceManagement/ResourceManager.h"

class InventoryUI : public cocos2d::ui::Widget {
public:
    static InventoryUI* create();

    InventoryUI();
    ~InventoryUI();

    bool init();
    void updateUI();  // 更新UI（比如更新物品列表）
    void click(cocos2d::Vec2);
    void attach(cocos2d::Vec2 pos);
    void detach();

    // Convert displayer coord into row and col in inventory
    cocos2d::Vec2 convertXYToRC(const cocos2d::Vec2&);
    // Convert row and col in inventory into displayer coord
    cocos2d::Vec2 convertRCToXY(const cocos2d::Vec2&);


private:
    static Inventory* inventory;
    static ItemManager* im;
    static ResourceManager* rm;

    cocos2d::Layer* attached;
    // 将所有物品精灵放在该Layer中，便于管理
    cocos2d::Layer* itemLayer;
    // 其他UI元素，比如物品格子、分页按钮等
};

#endif // __INVENTORY_UI_H__
