// HUD.cpp
#include "HUD.h"
#include "Player/Player.h"

USING_NS_CC;

HUD* HUD::instance = nullptr;
ResourceManager* HUD::rscm = nullptr;

HUD::HUD() :
	gameTime(nullptr),
	gameTimeLabel(nullptr),
	timerModel(nullptr),
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
	rscm = ResourceManager::getInstance();



	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto energyBarBackground = Sprite::create("UI/Screen/EnergyBar.png");
	energyBarBackground->setScale(4);
	energyBarBackground->setAnchorPoint(Vec2(1, 0));
	energyBarBackground->setPosition(visibleSize.width, 0);

	energyLabel = rscm->getLabel("Energy: 100", 24);
	//energyLabel->setSystemFontSize(24);
	energyLabel->setAnchorPoint(Vec2(1, 0));
	energyLabel->setPosition(visibleSize.width - 64, 0);

	timerModel = ProgressTimer::create(Sprite::create("UI/Screen/Timer.png"));
	timerModel->setType(ProgressTimer::Type::BAR);
	timerModel->setScale(4);
	timerModel->setAnchorPoint(Vec2(1, 1));
	timerModel->setPosition(visibleSize.width, visibleSize.height);
	timerModel->setPercentage(100);

	gameTime = GameTime::getInstance();
	gameTimeLabel = rscm->getLabel(gameTime->toString(), 26);
	gameTimeLabel->setAnchorPoint(Vec2(1, 1));
	gameTimeLabel->setPosition(visibleSize.width + 72, visibleSize.height - 20);
	this->schedule([this](float dt) {
		updateGameTimeHUD();
		}, 1.0f, "Game_time_update_key");

	this->addChild(energyBarBackground, 0);
	this->addChild(energyLabel, 1);
	this->addChild(timerModel, 0);
	this->addChild(gameTimeLabel, 1);

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
	timerModel->setPercentage(100.0 / PLAYER_MAX_STRENGTH * Player::getInstance()->getEnergy());
	energyLabel->setString("Energy: " + std::to_string(Player::getInstance()->getEnergy()));
}

void HUD::toggleVisibility(bool visible)
{
	this->setVisible(visible);
}
