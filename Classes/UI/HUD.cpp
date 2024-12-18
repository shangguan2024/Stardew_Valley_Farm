// HUD.cpp
#include "HUD.h"
#include "Player/Player.h"

HUD* HUD::instance = nullptr;

HUD::HUD() :
	strengthBar(nullptr),
	strengthLabel(nullptr),
	gameTime(nullptr),
	gameTimeLabel(nullptr)
{
}

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

// ³õÊ¼»¯ HUD
bool HUD::init()
{
	gameTime = GameTime::getInstance();
	gameTimeLabel = cocos2d::Label::createWithSystemFont(gameTime->toString(), "Consolas", 32);
	gameTimeLabel->setPosition(1000, 640);
	this->addChild(gameTimeLabel);
	this->schedule([this](float dt) {
		updateGameTimeHUD();
		}, 1.0f, "Game_time_update_key");

	auto strengthBarBackground = cocos2d::Sprite::create("UI/Buttons/CreateButton.png");
	strengthBarBackground->setPosition(150, 550);
	strengthBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("UI/Buttons/ExitButton.png"));
	strengthBar->setType(cocos2d::ProgressTimer::Type::BAR);
	strengthBar->setMidpoint(cocos2d::Vec2(0, 0));
	strengthBar->setBarChangeRate(cocos2d::Vec2(1, 0));
	strengthBar->setPercentage(100);
	strengthBar->setPosition(150, 550);
	strengthBar->setColor(cocos2d::Color3B(0, 255, 0));
	strengthLabel = cocos2d::Label::createWithSystemFont("Strength: 100", "Consolas", 24);
	strengthLabel->setPosition(100, 500);
	this->addChild(strengthBarBackground);
	this->addChild(strengthBar);
	this->addChild(strengthLabel);

	updateStrengthBarHUD();

	return true;
}

void HUD::updateGameTimeHUD()
{
	gameTime->updateTime();
	gameTimeLabel->setString(gameTime->toString());
}

void HUD::updateStrengthBarHUD()
{
	strengthBar->setPercentage(100.0 / PLAYER_MAX_STRENGTH * Player::getInstance()->getStrength());
	strengthLabel->setString("Strength: " + std::to_string(Player::getInstance()->getStrength()));
}

void HUD::toggleVisibility(bool visible)
{
	this->setVisible(visible);
}
