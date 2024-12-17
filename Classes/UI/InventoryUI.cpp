#include "InventoryUI.h"
#include "UI/UIManager.h"

InventoryUI::InventoryUI()
    : closeButton(nullptr)
{
}

InventoryUI::~InventoryUI()
{
}

InventoryUI* InventoryUI::create()
{
    InventoryUI* ret = new InventoryUI();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool InventoryUI::init()
{
    // 初始化界面
    closeButton = cocos2d::ui::Button::create("Buttons/MenuSceneButtons/ExitButton.png");
    closeButton->setPosition(cocos2d::Vec2(400, 300));
    closeButton->addClickEventListener([this](Ref* sender) {
        UIManager::getInstance()->hideInventoryUI();  // 点击关闭时隐藏背包
        });

    this->addChild(closeButton);
    auto testbackground = cocos2d::Sprite::create("Buttons/MenuSceneButtons/CreateButton.png");
    testbackground->setPosition(cocos2d::Vec2(600, 500));
    this->addChild(testbackground);

    return true;
}

void InventoryUI::updateUI()
{
    // 更新背包内容，比如显示物品列表
}
