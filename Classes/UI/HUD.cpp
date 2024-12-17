// HUD.cpp
#include "HUD.h"

HUD* HUD::instance = nullptr;

HUD::HUD() : _healthBar(nullptr), _scoreLabel(nullptr) {}

HUD::~HUD() {}

HUD* HUD::getInstance()
{
    if (!instance) {
        instance = create();
    }
    return instance;
}

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
    // ³õÊ¼»¯ HUD
    _healthBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("UI/Buttons/ExitButton.png"));
    _healthBar->setType(cocos2d::ProgressTimer::Type::BAR);
    _healthBar->setMidpoint(cocos2d::Vec2(0, 0));
    _healthBar->setBarChangeRate(cocos2d::Vec2(1, 0));
    _healthBar->setPercentage(100);
    _healthBar->setPosition(100, 550);
    this->addChild(_healthBar);

    _scoreLabel = cocos2d::Label::createWithSystemFont("Score: 0", "Arial", 24);
    _scoreLabel->setPosition(100, 500);
    this->addChild(_scoreLabel);

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
