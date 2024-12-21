/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     InventoryLayer.cpp
 * File Function: InventoryLayer类的实现
 * Author:        张翔
 * Update Date:   2024/12/14
 ****************************************************************/

#include "InventoryLayer.h"
#define backpos "chatlayerbackground2.png"
#define slotpos "Slot.png"
USING_NS_CC;

InventoryLayer* InventoryLayer::create()
{
    InventoryLayer* layer = new(std::nothrow) InventoryLayer();
    if (layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }

}

bool InventoryLayer::init()
{
    if (!Layer::init()) 
    {
        return false;
    }
    close();
}

void InventoryLayer::close() 
{
    // 设置打开背包按钮
    auto InventoryButton = HoverButton::create(slotpos, slotpos, slotpos);
    InventoryButton->setPosition(Vec2(Director::getInstance()->getWinSize().width - 100, 650) - Vec2(0, 100));
    InventoryButton->setContentSize(Size(50, 50));
    InventoryButton->setColor(ccc3(0, 128, 128));
    InventoryButton->addTouchEventListener([this, InventoryButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN)
            {
                open();
            }
        });

    this->removeAllChildren();

    this->addChild(InventoryButton, 1, "InventoryButton");

    auto currentItemBackground = Sprite::create(slotpos);
    currentItemBackground->setPosition(Vec2(100, 100));
    addChild(currentItemBackground, 1, "currentItemBackground");

    if (!Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).isEmpty())
    {
        auto currentItem = Sprite::create(Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).getItem()->image);
        currentItem->setPosition(Vec2(100, 100));
        currentItem->setContentSize(Size(36, 36));
        addChild(currentItem, 2, "currentItem");
    }
}

InventoryLayer::~InventoryLayer() 
{

}

void InventoryLayer::open()
{
    auto deleteInventoryButton = getChildByName("InventoryButton");
    if (deleteInventoryButton != nullptr)
    {
        removeChild(deleteInventoryButton);
    }
    auto deleteCurrentItem = getChildByName("currentItem");
    if (deleteCurrentItem != nullptr)
    {
        removeChild(deleteCurrentItem);
    }
    auto deleteCurrentItemBackground = getChildByName("currentItemBackground");
    if (deleteCurrentItem != nullptr)
    {
        removeChild(deleteCurrentItemBackground);
    }

    Size winSize = Director::getInstance()->getWinSize();

    // 设置背景
    auto background = Sprite::create(backpos);
    background->setContentSize(Size(winSize.width - 100, winSize.height - 100));
    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(Vec2(50, 50));
    background->setOpacity(128);
    this->addChild(background, 0, "background");

    // 设置格子
    for (int i = 0; i < DEFAULT_CAPACITY; i++)
    {
        auto slotButton = HoverButton::create(slotpos, slotpos, slotpos);
        slotButton->setPosition(Vec2(200, 400) + Vec2((i % 10) * 100, 0) - Vec2(0, (i / 10) * 100));
        slotButton->setContentSize(Size(50, 50));
        if(i == Inventory::getInstance()->getCurrHeldItem())
            slotButton->setColor(ccc3(0, 255, 0));
        slotButton->addTouchEventListener([this, i, slotButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
            {
                if (type == cocos2d::ui::Widget::TouchEventType::BEGAN)
                {
                    auto originalColor = slotButton->getColor();
                    this->getChildByName("slotButton" + std::to_string(Inventory::getInstance()->getCurrHeldItem()))->setColor(originalColor);
                    // 修改手持物品格子
                    Inventory::getInstance()->changeCurrHeldItem(i);

                    auto deleteCurrentItem = getChildByName("currentItem");
                    if (deleteCurrentItem != nullptr)
                    {
                        removeChild(deleteCurrentItem);
                    }
                    if (!Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).isEmpty())
                    {
                        auto currentItem = Sprite::create(Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).getItem()->image);
                        currentItem->setPosition(Vec2(100, 100));
                        currentItem->setContentSize(Size(36, 36));
                        addChild(currentItem, 2, "currentItem");
                    }
                    slotButton->setColor(ccc3(0, 255, 0));
                }
            });
        this->addChild(slotButton, 1, "slotButton" + std::to_string(i));
    }

    // 设置格子中的物品图片
    for (int i = 0; i < DEFAULT_CAPACITY; i++)
    {
        if (!Inventory::getInstance()->getSlot(i).isEmpty())
        {
            auto itemIcon = Sprite::create(Inventory::getInstance()->getSlot(i).getItem()->image);
            itemIcon->setContentSize(Size(36, 36));
            itemIcon->setPosition(this->getChildByName("slotButton" + std::to_string(i))->getPosition());
            addChild(itemIcon, 2, "itemIcon" + std::to_string(i));
        }
    }
    // 手持物品
    auto currentItemBackground = Sprite::create(slotpos);
    currentItemBackground->setPosition(Vec2(100, 100));
    this->addChild(currentItemBackground, 1, "currentItemBackground");
    if (!Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).isEmpty()) 
    {
        auto currentItem = Sprite::create(Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).getItem()->image);
        currentItem->setPosition(Vec2(100, 100));
        currentItem->setContentSize(Size(36, 36));
        this->addChild(currentItem, 2, "currentItem");
    }
    // 关闭按钮
    auto closeButton = HoverButton::create("CloseSlot.png", slotpos, "CloseSlot.png");
    closeButton->setPosition(Vec2(winSize.width - 100, 650));
    closeButton->setContentSize(Size(50, 50));
    closeButton->addTouchEventListener([this, closeButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN)
            {
                close();
            }
        });
    this->addChild(closeButton, 1, "closeButton");

}