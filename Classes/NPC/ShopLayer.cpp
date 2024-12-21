#include "ShopLayer.h"

USING_NS_CC;

ShopLayer::ShopLayer() 
{

}

ShopLayer* ShopLayer::create() 
{
    ShopLayer* layer = new(std::nothrow) ShopLayer();
    if (layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    else 
    {
        delete layer;
        return nullptr;
    }
}

// 初始化
bool ShopLayer::init() 
{
    if (!Layer::init()) 
    {
        return false;
    }

}

// 设置对话/交易/委托/赠送的NPC
void ShopLayer::setNPC(NPC* npc) 
{
    _currentNPC = npc;
}

// 获取背包物品所在格子
Slot& ShopLayer::getInventorySlots(std::shared_ptr<Item> item)
{
    return Inventory::getInstance()->getSlot(Inventory::getInstance()->findItem(item));
}

// 进行交易 失去_PaidItems 得到_ShopItems 返回交易是否成功
bool ShopLayer::tradeItems() 
{
    // 检查背包中是否有委托物品
    for (int i = 0; i < _ShopItems.size(); i++)
    {
        // 定位委托物品
        if (_ShopItemsType[i] == TASK_PAID)
        {
            auto paid = _ShopItems[i];
            if (Inventory::getInstance()->findItem(paid) == -1)
            {
                return false;
            }
        }
    }
    // 删除委托物品
    for (int i = 0; i < _ShopItems.size(); i++)
    {
        // 定位委托物品
        if (_ShopItemsType[i] == TASK_PAID) 
        {
            auto paid = _ShopItems[i];
            if (Inventory::getInstance()->findItem(paid) != -1)
            {
                // 从背包中取出对应paid物品
                getInventorySlots(std::shared_ptr<Item>(paid)).changeQuantity(_ShopItemsNum[i]);
                continue;
            }
        }
    }
    // 向背包添加奖励
    for (int i = 0; i < _ShopItems.size(); i++)
    {
        // 定位奖励
        if (_ShopItemsType[i] == TASK_REWARD) 
        {
            // 添加奖励
            Inventory::getInstance()->addItem(std::shared_ptr<Item>(_ShopItems[i]), _ShopItemsNum[i]);
        }
    }

    return true;
}

// 更新商店内物品及其显示
void ShopLayer::UpdateShopItems() 
{

    Size winSize = Director::getInstance()->getWinSize();

    // 菜单界面 放置购买/交付委托/赠送礼物的button
    
    // 设置剩余金钱数量显示
    auto bullet = Label::create(std::to_string(Inventory::getInstance()->getCoin()), "", 30);
    bullet->setPosition(Vec2(40, 20));
    bullet->setColor(ccc3(0, 0, 0));
    this->addChild(bullet, 3);

    // 显示商店内已有物品
    for (int i = 0; i < _ShopItems.size(); i++)
    {
        if (_ShopItemsType[i] == SHOP_BUY || _ShopItemsType[i] == SHOP_SELL)
        {
            // 添加物品图标
            auto item = _ShopItems[i];
            auto itemIcon = Sprite::create(item->image);
            itemIcon->setContentSize(Size(36, 36));
            itemIcon->setPosition(Vec2(50, winSize.height - 50) + Vec2(60, 0) - i * Vec2(0, 60));
            this->addChild(itemIcon, 1, enumToString(item->getType()));

            // 添加购买按钮 金钱->物品
            auto itemButton = HoverButton::create("hoverBox.png", "hoverBox.png", "hoverBox.png");
            itemButton->setPosition(itemIcon->getPosition() - Vec2(40, 0));
            itemButton->setContentSize(Size(10, 10));

            Label* itemName;

            switch (_ShopItemsType[i])
            {
                case SHOP_BUY:
                    
                    itemName = Label::create(enumToString(item->getType()) + " BUY $" + std::to_string(item->getprice()) + " last *" + std::to_string(_ShopItemsNum[i]), "", 30);

                    itemButton->addTouchEventListener([this, i, bullet,itemButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                        {
                            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN){
                                if (!Inventory::getInstance()->isSlotFull() || Inventory::getInstance()->isCoinEnough(_ShopItems[i]->getprice()) || _ShopItemsNum[i] != 0)
                                {
                                    if (Inventory::getInstance()->getCoin() > _ShopItems[i]->getprice())
                                    {
                                        Inventory::getInstance()->changeCoin(0 - _ShopItems[i]->getprice());
                                        Inventory::getInstance()->addItem(std::shared_ptr<Item>(_ShopItems[i]), 1);
                                        _ShopItemsNum[i]--;
                                        bullet->setString(std::to_string(Inventory::getInstance()->getCoin()));
                                    }
                                    else
                                    {
                                        itemButton->setColor(ccc3(255, 0, 0));
                                    }
                                }
                            }
                        });

                    break;
                case SHOP_SELL:
                    itemName = Label::create(enumToString(item->getType()) + " SELL $" + std::to_string(item->getprice()), "", 30);

                    itemButton->addTouchEventListener([this, i, bullet](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                        {
                            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN){
                                if (Inventory::getInstance()->findItem(std::shared_ptr<Item>(_ShopItems[i])) != -1)
                                {
                                    Inventory::getInstance()->getSlot(Inventory::getInstance()->findItem(std::shared_ptr<Item>(_ShopItems[i]))).changeQuantity(1);
                                    Inventory::getInstance()->changeCoin(_ShopItems[i]->getprice());
                                    bullet->setString(std::to_string(Inventory::getInstance()->getCoin()));
                                }
                            }
                        });

                    break;
            }

            this->addChild(itemButton, 2);

            // 添加物品类型
            itemName->setAnchorPoint(Vec2(0, 0.5));
            itemName->setPosition(itemIcon->getPosition() + Vec2(itemIcon->getContentSize().width, 0));
            itemName->setColor(ccc3(0, 0, 0));
            this->addChild(itemName, 1);

            // 添加物品描述
            auto itemDescription = Label::create(item->getDescription(), "", 30);
            itemDescription->setAnchorPoint(Vec2(0, 0.5));
            itemDescription->setPosition(itemName->getPosition() + Vec2(0, itemName->getContentSize().height));
            itemDescription->setColor(ccc3(0, 0, 0));
            this->addChild(itemDescription, 1);
        }
    }

    // 显示委托
    {
        // 添加交付按钮
        auto TaskButton = HoverButton::create("hoverBox.png", "hoverBox.png", "hoverBox.png");
        TaskButton->setPosition(Vec2(110, 300));
        TaskButton->setContentSize(Size(10, 10));
        // 委托内容显示
        std::string rewardstr = " ";
        std::string paidstr = " ";
        for (int i = 0; i < _ShopItems.size(); i++)
        {
            if (_ShopItemsType[i] == TASK_PAID)
            {
                auto a = _ShopItems[i];
                _ShopItems[i]->getType();
                paidstr += enumToString(_ShopItems[i]->getType()) + "*" + std::to_string(_ShopItemsNum[i]) + " ";
            }
            else if (_ShopItemsType[i] == TASK_REWARD)
                rewardstr += enumToString(_ShopItems[i]->getType()) + "*" + std::to_string(_ShopItemsNum[i]) + " ";
        }
        auto TaskRewardLabel = Label::create("task reward:" + rewardstr, "", 30);
        TaskRewardLabel->setAnchorPoint(Vec2(0, 0.5));
        TaskRewardLabel->setPosition(TaskButton->getPosition() + Vec2(36, 0));
        TaskRewardLabel->setColor(ccc3(0, 0, 0));
        addChild(TaskRewardLabel, 2, "TaskRewardLabel");

        auto TaskPaidLabel = Label::create("task paid:" + paidstr, "", 30);
        TaskPaidLabel->setAnchorPoint(Vec2(0, 0.5));
        TaskPaidLabel->setPosition(TaskButton->getPosition() + Vec2(36, -30));
        TaskPaidLabel->setColor(ccc3(0, 0, 0));
        addChild(TaskPaidLabel, 2, "TaskPaidLabel");

        TaskButton->addTouchEventListener([this, TaskButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
            {
                if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                    // 如果交付成功
                    if (tradeItems() == 1)
                    {
                        auto TaskFinishLabel = Label::create("FINISH", "", 30);
                        TaskFinishLabel->setPosition(TaskButton->getPosition());
                        TaskFinishLabel->setColor(ccc3(255, 0, 0));
                        addChild(TaskFinishLabel, 3, "TaskFinishLabel");
                        TaskButton->setEnabled(false);
                    }
                }
            });
        addChild(TaskButton, 2, "TaskButton");

    }
}

// 向商店中_ShopItems添加物品
void ShopLayer::InsertShopItems(std::shared_ptr<Item> _item, int num, ShopType type)
{
    for (int i = 0; i < _ShopItems.size(); i++)
    {
        // 已有相同操作类型的物品
        if (_ShopItems[i] == _item && _ShopItemsType[i] == type) 
        {
            _ShopItemsNum[i] += num;
            return;
        }
    }

    _ShopItems.push_back(_item);
    _ShopItemsNum.push_back(num);
    _ShopItemsType.push_back(type);
}

void ShopLayer::DeleteShop() 
{
    this->removeAllChildren();
}