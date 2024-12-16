/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     ChatLayer.cpp
 * File Function: ChatLayer类的实现
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#include "ChatLayer.h"

ChatLayer::ChatLayer() : currentNPC(nullptr), isStoreOpen(false) {}

ChatLayer::~ChatLayer() {}

bool ChatLayer::init(NPC* npc)
{
    if (!Layer::init()) {
        return false;
    }

    // 创建对话框背景

    // 创建人物头像
    
    // 创建对话文本标签
    
    // 创建对话按钮(点击推进对话)
    
    // 创建事件按钮(点击后弹出 买卖东西，制作物品 的界面) 目前不用细做，有个界面背景就行(之后再另分类细做) 但需要点击一次打开，点击第二次关闭

    // 创建关闭按钮(退出对话)

    return true;
}

ChatLayer* ChatLayer::create(NPC* npc)
{
    ChatLayer* layer = new(std::nothrow) ChatLayer();
    if (layer && layer->init(npc)) {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}

void ChatLayer::updateDialog()
{

}

void ChatLayer::closeChat()
{
    currentNPC->jumpToDialog(0);
    this->removeFromParentAndCleanup(true);
}
