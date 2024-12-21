#include "PlayerController.h"
#include "UI/UIManager.h"

PlayerController* PlayerController::instance = nullptr;

PlayerController* PlayerController::getInstance()
{
	if (instance == nullptr) {
		instance = new PlayerController;
		if (!instance || !instance->init()) {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

void PlayerController::update()
{
	if (player->isFreeze())return;
	updateDirection();
}

PlayerController::PlayerController() :
	player(nullptr),
	inventory(nullptr)
{
}

PlayerController::~PlayerController()
{
	InputManager::getInstance()->resetCurrentKeyControlMode("player");
	delete instance;
}

bool PlayerController::init()
{
	player = Player::getInstance();
	InputManager::getInstance()->registerKeyCallbackFunc("player", [this](cocos2d::EventKeyboard::KeyCode keyCode) {
		onKeyPressed(keyCode);
		});
	InputManager::getInstance()->setCurrentKeyControlMode("player");
	return true;
}

void PlayerController::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode) {
	case cocos2d::EventKeyboard::KeyCode::KEY_E:
		toggleInventory();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_N:
		GameTime::getInstance()->jumpToNextMorning();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_T:
		player->addEnergy(-1);
		break;
	default:
		break;
	}

	Player::getInstance()->unFreeze();
}

void PlayerController::updateDirection()
{
	cocos2d::Vec2 dir = cocos2d::Vec2::ZERO;
	auto inputManager = InputManager::getInstance();

	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_W, "player")) {
		dir.y += 1.0f;
	}
	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_A, "player")) {
		dir.x -= 1.0f;
	}
	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_S, "player")) {
		dir.y -= 1.0f;
	}
	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_D, "player")) {
		dir.x += 1.0f;
	}

	player->setDirection(dir);
}

void PlayerController::toggleInventory()
{
	if (UIManager::getInstance()->isUIActive()) {
		UIManager::getInstance()->hideInventoryUI();
	}
	else {
		UIManager::getInstance()->showInventoryUI();
	}
}
