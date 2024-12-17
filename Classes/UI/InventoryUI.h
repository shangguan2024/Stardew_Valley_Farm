#ifndef __INVENTORY_UI_H__
#define __INVENTORY_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class InventoryUI : public cocos2d::ui::Widget {
public:
    static InventoryUI* create();

    InventoryUI();
    ~InventoryUI();

    bool init();

    void updateUI();  // 更新UI（比如更新物品列表）

private:
    cocos2d::ui::Button* closeButton;
    // 其他UI元素，比如物品格子、分页按钮等
};

#endif // __INVENTORY_UI_H__
