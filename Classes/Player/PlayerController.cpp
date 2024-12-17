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
	updateDirection();
}

PlayerController::PlayerController() :
	player(nullptr),
	inventory(nullptr)
{
}

PlayerController::~PlayerController()
{
	InputManager::getInstance()->popCurrentKeyControlMode();
	delete instance;
}

bool PlayerController::init()
{
	player = Player::getInstance();
	InputManager::getInstance()->registerKeyCallbackFunc(KeyControlMode::PLAYER_CONTROL, [this](cocos2d::EventKeyboard::KeyCode keyCode) {
		onKeyPressed(keyCode);
		});
	InputManager::getInstance()->setCurrentKeyControlMode(KeyControlMode::PLAYER_CONTROL);
	return true;
}

void PlayerController::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode) {
	case cocos2d::EventKeyboard::KeyCode::KEY_E:
		toggleInventory();
		break;
	default:
		break;
	}
}

void PlayerController::updateDirection()
{
	cocos2d::Vec2 dir = cocos2d::Vec2::ZERO;
	auto inputManager = InputManager::getInstance();

	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_W, KeyControlMode::PLAYER_CONTROL)) {
		dir.y += 1.0f;
	}
	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_A, KeyControlMode::PLAYER_CONTROL)) {
		dir.x -= 1.0f;
	}
	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_S, KeyControlMode::PLAYER_CONTROL)) {
		dir.y -= 1.0f;
	}
	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_D, KeyControlMode::PLAYER_CONTROL)) {
		dir.x += 1.0f;
	}

	player->setDirection(dir);
}

void PlayerController::toggleInventory()
{
	UIManager::getInstance()->showInventoryUI();
}
