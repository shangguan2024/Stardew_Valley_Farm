#include "InputManager.h"
#include "UI/UIManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() :
	keyboardListener(nullptr),
	mouseListener(nullptr),
	mousePosition(cocos2d::Vec2::ZERO)
{
}

InputManager::~InputManager()
{
	unRegisterEventListeners();
}

bool InputManager::init()
{
	registerEventListeners();
	return true;
}

void InputManager::registerEventListeners()
{
	// ���������¼�������
	keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener, 1);

	// ��������¼�������
	mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(InputManager::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(InputManager::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(InputManager::onMouseUp, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(mouseListener, 1);
}

void InputManager::unRegisterEventListeners()
{
	// ע���¼�������
	if (keyboardListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);
	}
	if (mouseListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(mouseListener);
	}
}

void InputManager::registerKeyCallbackFunc(KeyControlMode mode, std::function<void(cocos2d::EventKeyboard::KeyCode)> callback)
{
	if (keyCallbackFuncs[mode]) {
		return;
	}
	keyCallbackFuncs[mode] = callback;
}

void InputManager::registerMouseCallbackFunc(MouseControlMode mode, std::function<void(cocos2d::EventMouse::MouseButton)> callback)
{
	if (mouseCallbackFuncs[mode]) {
		return;
	}
	mouseCallbackFuncs[mode] = callback;
}

void InputManager::setCurrentKeyControlMode(KeyControlMode mode)
{
	keyControlMode.push(mode);
}

void InputManager::setCurrentMouseControlMode(MouseControlMode mode)
{
	mouseControlMode.push(mode);
}

void InputManager::popCurrentKeyControlMode()
{
	keyControlMode.pop();
}

void InputManager::popCurrentMouseControlMode()
{
	mouseControlMode.pop();
}

// ������̰����¼�
void InputManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	CCLOG("Key pressed: %d", keyCode);
	keyStates[keyCode] = true;
	if (!keyControlMode.empty() && keyCallbackFuncs[keyControlMode.top()]) {
		keyCallbackFuncs[keyControlMode.top()](keyCode);
	}
}

// ��������ͷ��¼�
void InputManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	keyStates[keyCode] = false;
	CCLOG("Key released: %d", keyCode);
}

// ��������ƶ��¼�
void InputManager::onMouseMove(cocos2d::Event* event)
{
	if (UIManager::getInstance()->isUIActive()) {
		return;
	}
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	// CCLOG("Mouse moved to position: (%f, %f)", mouseEvent->getCursorX(), mouseEvent->getCursorY());
	mousePosition = cocos2d::Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
}

// ������갴���¼�
void InputManager::onMouseDown(cocos2d::Event* event)
{
	if (UIManager::getInstance()->isUIActive()) {
		return;
	}
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	CCLOG("Mouse button pressed: %d", mouseEvent->getMouseButton());
	mouseButtonStates[mouseEvent->getMouseButton()] = true;
	if (!mouseControlMode.empty() && mouseCallbackFuncs[mouseControlMode.top()]) {
		mouseCallbackFuncs[mouseControlMode.top()](mouseEvent->getMouseButton());
	}
}

// ��������ͷ��¼�
void InputManager::onMouseUp(cocos2d::Event* event)
{
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	CCLOG("Mouse button released: %d", mouseEvent->getMouseButton());
	mouseButtonStates[mouseEvent->getMouseButton()] = false;
}

bool InputManager::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, KeyControlMode mode)
{
	if (keyControlMode.empty()) {
		return false;
	}
	return keyControlMode.top() == mode && keyStates[keyCode];
}

bool InputManager::isKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, KeyControlMode mode)
{
	if (keyControlMode.empty()) {
		return false;
	}
	return keyControlMode.top() == mode && !keyStates[keyCode];
}

bool InputManager::isMousePressed(cocos2d::EventMouse::MouseButton button, MouseControlMode mode)
{
	if (mouseControlMode.empty()) {
		return false;
	}
	return mouseControlMode.top() == mode && mouseButtonStates[button];
}

bool InputManager::isMouseReleased(cocos2d::EventMouse::MouseButton button, MouseControlMode mode)
{
	if (mouseControlMode.empty()) {
		return false;
	}
	return mouseControlMode.top() == mode && !mouseButtonStates[button];
}

const cocos2d::Vec2* InputManager::getMousePosition(MouseControlMode mode) const
{
	if (mouseControlMode.empty()) {
		return nullptr;
	}
	if (mouseControlMode.top() != mode) {
		return nullptr;
	}
	return &mousePosition;
}

void InputManager::clearPollingStates()
{
	keyStates.clear();
	mouseButtonStates.clear();
}

InputManager* InputManager::getInstance()
{
	if (instance == nullptr) {
		instance = new InputManager();
		instance->init();
	}
	return instance;
}
