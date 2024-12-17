// HUD.cpp
#include "HUD.h"

HUD::HUD() : _healthBar(nullptr), _scoreLabel(nullptr), _hoverButton(nullptr) {}

HUD::~HUD() {}

HUD* HUD::create()
{
    HUD* ret = new HUD();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool HUD::init()
{
    // 初始化 HUD
    // _healthBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("health_bar.png"));
    // _healthBar->setType(cocos2d::ProgressTimer::Type::BAR);
    // _healthBar->setMidpoint(cocos2d::Vec2(0, 0));
    // _healthBar->setBarChangeRate(cocos2d::Vec2(1, 0));
    // _healthBar->setPercentage(100);
    // _healthBar->setPosition(100, 550);
    // this->addChild(_healthBar);

    // _scoreLabel = cocos2d::Label::createWithSystemFont("Score: 0", "Arial", 24);
    // _scoreLabel->setPosition(100, 500);
    // this->addChild(_scoreLabel);

    // 创建 HoverButton
    // _hoverButton = HoverButton::create("button_normal.png", "button_hover.png", "button_disabled.png");
    // _hoverButton->setPosition({ 300, 300 });
    // this->addChild(_hoverButton);

    // // 监听鼠标事件
    // auto listener = cocos2d::EventListenerMouse::create();
    // listener->onMouseMove = CC_CALLBACK_1(HUD::onButtonHover, this);
    // _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HUD::updateHUD(float health, int score)
{
    _healthBar->setPercentage(health);
    _scoreLabel->setString("Score: " + std::to_string(score));
}

void HUD::toggleVisibility(bool visible)
{
    this->setVisible(visible);
}

void HUD::onButtonClick(cocos2d::Ref* sender)
{
    CCLOG("Button clicked!");
}
