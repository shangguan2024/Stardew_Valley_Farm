/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     ChatLayer.h
 * File Function: ChatLayer类的定义
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#ifndef _CHATLAYER_H_
#define _CHATLAYER_H_

#include "cocos2d.h"
#include "NPC.h"
#include "../Button/HoverButton.h"

class ChatLayer:public cocos2d::Layer
{
public:
    // 初始化方法
    virtual bool init(NPC* npc);

    // 创建 ChatLayer
    static ChatLayer* create(NPC* npc);

private:
    ChatLayer();      // 构造函数
    ~ChatLayer();     // 析构函数

    // 更新对话内容
    void updateDialog();

    // 按钮的回调函数
    void chatButtonCallBack(Ref* pSender);
    void eventButtonCallBack(Ref* pSender);
    void quitButtonCallBack(Ref* pSender);
    void storequitButtonCallBack(Ref* pSender);

    // 关闭对话框
    void closeChat();

    NPC* currentNPC;  // 当前的NPC

    bool isStoreOpen; // 商店界面是否打开

};

#endif // _CHATLAYER_H_

/* ChatLayer示例
* 添加到FarmYardScene.cpp中生效
auto npc = NPC::create("Player/Sandy.png", ALEX);
if (!npc)
{
    CCLOG("Failed to create NPC!");
}
this->addChild(npc);
auto chatlayer = ChatLayer::create(npc);
this->addChild(chatlayer,1,"chatlayer");
chatlayer->setAnchorPoint(Vec2(0, 0));
chatlayer->setPosition(Vec2(_camera->getPosition3D().x, _camera->getPosition3D().y));
chatlayer->setCameraMask(unsigned short(CameraFlag::USER1));
*/
