// HUD.cpp
#include "HUD.h"
#include "Player/Player.h"

USING_NS_CC;

HUD* HUD::instance = nullptr;
ResourceManager* HUD::resourceManager = nullptr;

HUD::HUD() :
	gameTime(nullptr),
	gameTimeLabel(nullptr),
	energyBar(nullptr),
	energyLabel(nullptr)
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
	resourceManager = ResourceManager::getInstance();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Energy bar
	auto energyBarBackground = Sprite::create("UI/Screen/EnergyBarBackground.png");
	energyBarBackground->setScale(4);
	energyBarBackground->setAnchorPoint(Vec2(1, 0));
	energyBarBackground->setPosition(visibleSize.width, 0);

	energyLabel = resourceManager->getLabel("Energy: 100", 24);
	energyLabel->setAnchorPoint(Vec2(1, 0));
	energyLabel->setPosition(visibleSize.width - 64, 0);

	energyBar = ProgressTimer::create(Sprite::create("UI/Screen/EnergyBar.png"));
	energyBar->setColor(cocos2d::Color3B(0, 255, 0));
	energyBar->setScale(4);
	energyBar->setType(ProgressTimer::Type::BAR);
	energyBar->setMidpoint(Vec2(0, 0));
	energyBar->setBarChangeRate(Vec2(0, 1));
	energyBar->setAnchorPoint(Vec2(1, 0));
	energyBar->setPosition(visibleSize.width, 8);
	energyBar->setPercentage(100);

	this->addChild(energyBarBackground, 0);
	this->addChild(energyLabel, 1);
	this->addChild(energyBar, 2);

	updateStrengthBarHUD();

	// Game time
	auto gameTimeBackground = Sprite::create("UI/Screen/Timer.png");
	gameTimeBackground->setScale(4);
	gameTimeBackground->setAnchorPoint(Vec2(1, 1));
	gameTimeBackground->setPosition(visibleSize.width, visibleSize.height);

	gameTime = GameTime::getInstance();
	gameTimeLabel = resourceManager->getLabel(gameTime->toString(), 22);
	gameTimeLabel->setAnchorPoint(Vec2(1, 1));
	gameTimeLabel->setPosition(visibleSize.width - 42, visibleSize.height - 20);
	this->schedule([this](float dt) {
		updateGameTimeHUD();
		}, 1.0f, "Game_time_update_key");
	this->addChild(gameTimeBackground, 0);
	this->addChild(gameTimeLabel, 1);

	return true;
}

void HUD::updateGameTimeHUD()
{
	gameTime->updateTime();
	gameTimeLabel->setString(gameTime->toString());
}

void HUD::updateStrengthBarHUD()
{
	energyBar->setPercentage(100.0 / PLAYER_MAX_STRENGTH * Player::getInstance()->getEnergy());
	energyLabel->setString("Energy: " + std::to_string(Player::getInstance()->getEnergy()));
}

void HUD::toggleVisibility(bool visible)
{
	this->setVisible(visible);
}
