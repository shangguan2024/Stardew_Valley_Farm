#include "FishingGame.h"

USING_NS_CC;

FishingGame* FishingGame::create()
{
    FishingGame* ret = new FishingGame();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool FishingGame::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();

    // 设置背景
    fishingBar = Sprite::create("chatlayerbackground2.png");
    fishingBar->setAnchorPoint(Vec2(0.5, 0.5));
    fishingBar->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(fishingBar, 0, "fishingBar");
    if (fishingBar == nullptr) 
    {
        CCLOG("ji");
    }
    // 设置鱼竿位置
    fishingRod = Sprite::create("fishing_rod.png");
    fishingRod->setContentSize(Size(fishingRod->getContentSize().width, fishingBar->getContentSize().height));
    fishingRod->setPosition(Vec2(fishingBar->getPosition().x-0.3 * fishingBar->getContentSize().width, fishingBar->getPosition().y));
    this->addChild(fishingRod, 2, "fishingRod");
    // 设置钓鱼条
    auto fishingPos = Sprite::create("close.png");
    fishingPos->setPosition(fishingBar->getPosition());
    this->addChild(fishingPos, 1, "fishingPos");

    // 创建背景
    auto menu = Menu::create();
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 0, "menu");
    // 设置钓鱼按钮
    auto fishingButton = HoverButton::create("Buttons/MenuSceneButtons/LoadButton.png",
        "Buttons/MenuSceneButtons/LoadButton.png",
        "Buttons/MenuSceneButtons/LoadButton.png");
    fishingButton->setAnchorPoint(Vec2(0.5, 0));
    fishingButton->setPosition(Vec2(fishingBar->getPosition().x, fishingBar->getPosition().y + fishingBar->getContentSize().height/2));
    fishingButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) mutable {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            auto moveAction = MoveBy::create(0.3f, Vec2(20, 0));
            this->getChildByName("fishingRod")->runAction(moveAction);

            //fishingRod->setPosition(fishingRod->getPosition() + Vec2(10, 0));
        }
        });
    this->addChild(fishingButton, 0, "fishingButton");
    // 设置进度条
    auto loadingBar = ui::LoadingBar::create("close.png");
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    loadingBar->setPosition(fishingBar->getPosition() - Vec2(0, fishingBar->getContentSize().height) / 2);
    loadingBar->setPercent(1);
    this->addChild(loadingBar, 2, "loadingBar");
    // 设置剩余时间显示
    auto lasttime = Label::create(std::to_string(fishingTime), "", 40);
    lasttime->setPosition(fishingButton->getPosition());
    lasttime->setColor(ccc3(0, 0, 0));
    this->addChild(lasttime, 3, "lasttime");

    this->setCameraMask(unsigned short(CameraFlag::USER1));
    return true;
}

void FishingGame::fishingEnd() 
{
    this->removeFromParentAndCleanup(true);
}

bool FishingGame::fishingUpdate(float delta)
{
    if (fishingTime <= 0) 
    {
        _fishCaught = 0;
        return true;
    }
    else if (dynamic_cast<ui::LoadingBar*>(this->getChildByName("loadingBar"))->getPercent() >= 100) 
    {
        _fishCaught = 1;
        return true;
    }
    else
    {
        fishingTime--;
        auto lasttime = dynamic_cast<Label*>(this->getChildByName("lasttime"));
        lasttime->setString(std::to_string(fishingTime));
        
        if (this->getChildByName("fishingRod")->getPosition().x >= this->getChildByName("fishingBar")->getPosition().x - this->getChildByName("fishingBar")->getContentSize().width / 2)
        {
            auto moveAction = MoveBy::create(1.0f, Vec2(-60, 0));
            this->getChildByName("fishingRod")->runAction(moveAction);
            //this->getChildByName("fishingRod")->setPosition(this->getChildByName("fishingRod")->getPosition() - Vec2(15, 0));
        }
        if (this->getChildByName("fishingRod")->getPosition().x <= this->getChildByName("fishingPos")->getPosition().x + this->getChildByName("fishingPos")->getContentSize().width / 2 && this->getChildByName("fishingRod")->getPosition().x >= this->getChildByName("fishingPos")->getPosition().x - this->getChildByName("fishingPos")->getContentSize().width / 2)
        {
            auto newpercent = dynamic_cast<ui::LoadingBar*>(this->getChildByName("loadingBar"))->getPercent();
            dynamic_cast<ui::LoadingBar*>(this->getChildByName("loadingBar"))->setPercent(newpercent + 10);
        }
    }
    return false;
}

bool FishingGame::FishingResult()
{
    if (_fishCaught) 
    {
        return true;
    }
    return false;
}

bool FishingGame::FishingGameStart()
{
    return true;
}

bool FishingGame::Update(float delta)
{
    if (fishingUpdate(delta)) 
    {
        return true;
    }
    return false;
}

FishingGame::FishingGame() : fishingTime(30),_fishCaught(false)
{
    
}

FishingGame::~FishingGame() {}