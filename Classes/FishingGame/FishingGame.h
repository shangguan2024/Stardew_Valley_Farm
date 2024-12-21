#pragma once
#include "Classes/Item/Item.h"
#include "Classes/Item/Tool.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Classes/Button/HoverButton.h"

class FishingGame : public cocos2d::Layer
{
private:
    int fishingTime;                // 钓鱼的总时长
    bool _fishCaught;               // 是否成功钓到鱼
    cocos2d::Sprite* fishingBar;    // 显示钓鱼进度的精灵
    cocos2d::Sprite* fishingRod;    // 钓竿的精灵
    cocos2d::Label* resultLabel;    // 显示结果的文字

    // 钓鱼更新，逐渐填满进度条
    bool fishingUpdate(float delta);
    // 开始上钩小游戏
    bool FishingGameStart();
public:
    // 构造函数
    FishingGame();
    // 析构函数
    ~FishingGame();
    // 完成钓鱼后的处理
    bool FishingResult();
    // 钓鱼结束 释放内存
    void fishingEnd();
    // 上钩小游戏更新
    bool Update(float delta);

    // 创建场景
    static FishingGame* create();

    // 初始化方法
    virtual bool init();
};

/*
* FishingGame示例
* 添加到FarmYardScene.cpp的init中生效
    auto fishing = FishingGame::create();
    this->addChild(fishing, 10, "fishing");

    schedule([this](float delta)
        {
            auto fishing = dynamic_cast<FishingGame*>(this->getChildByName("fishing"));
            if (fishing != nullptr)
            {
                if (fishing->Update(delta))
                {
                    fishing->FishingResult();
                    fishing->fishingEnd();
                }
            }
        }, 1.0f, "fishing_update_key");


*添加到update中终止运行

    if (this->getChildByName("fishing") == nullptr)
    {
        unschedule("fishing_update_key");
    }



*/