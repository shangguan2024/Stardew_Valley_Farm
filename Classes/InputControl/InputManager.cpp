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
	// 创建键盘事件监听器
	keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener, 1);

	// 创建鼠标事件监听器
	mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(InputManager::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(InputManager::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(InputManager::onMouseUp, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(mouseListener, 1);
}

void InputManager::unRegisterEventListeners()
{
	// 注销事件监听器
	if (keyboardListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);
	}
	if (mouseListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(mouseListener);
	}
}

void InputManager::registerKeyCallbackFunc(const std::string& name, std::function<void(cocos2d::EventKeyboard::KeyCode)> callback)
{
	if (keyCallbackFuncs[name]) {
		return;
	}
	keyCallbackFuncs[name] = callback;
}

void InputManager::registerMouseCallbackFunc(const std::string& name, std::function<void(cocos2d::EventMouse::MouseButton)> callback)
{
	if (mouseCallbackFuncs[name]) {
		return;
	}
	mouseCallbackFuncs[name] = callback;
}

void InputManager::setCurrentKeyControlMode(const std::string& name)
{
	keyControlMode = name;
}

void InputManager::setCurrentMouseControlMode(const std::string& name)
{
	mouseControlMode = name;
}

void InputManager::resetCurrentKeyControlMode(const std::string& name)
{
	if (keyControlMode == name)keyControlMode = "";
}

void InputManager::resetCurrentMouseControlMode(const std::string& name)
{
	if (mouseControlMode == name)mouseControlMode = "";
}

// 处理键盘按下事件
void InputManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	CCLOG("Key pressed: %d", keyCode);
	keyStates[keyCode] = true;
	if (keyControlMode != "" && keyCallbackFuncs[keyControlMode]) {
		keyCallbackFuncs[keyControlMode](keyCode);
	}
}

// 处理键盘释放事件
void InputManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	keyStates[keyCode] = false;
	CCLOG("Key released: %d", keyCode);
}

// 处理鼠标移动事件
void InputManager::onMouseMove(cocos2d::Event* event)
{
	if (UIManager::getInstance()->isUIActive()) {
		return;
	}
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	// CCLOG("Mouse moved to position: (%f, %f)", mouseEvent->getCursorX(), mouseEvent->getCursorY());
	mousePosition = cocos2d::Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
}

// 处理鼠标按下事件
void InputManager::onMouseDown(cocos2d::Event* event)
{
	if (UIManager::getInstance()->isUIActive()) {
		return;
	}
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	CCLOG("Mouse button pressed: %d", mouseEvent->getMouseButton());
	mouseButtonStates[mouseEvent->getMouseButton()] = true;
	if (mouseControlMode != "" && mouseCallbackFuncs[mouseControlMode]) {
		mouseCallbackFuncs[mouseControlMode](mouseEvent->getMouseButton());
	}
}

// 处理鼠标释放事件
void InputManager::onMouseUp(cocos2d::Event* event)
{
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	CCLOG("Mouse button released: %d", mouseEvent->getMouseButton());
	mouseButtonStates[mouseEvent->getMouseButton()] = false;
}

bool InputManager::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, const std::string& name)
{
	if (keyControlMode.empty()) {
		return false;
	}
	return keyControlMode == name && keyStates[keyCode];
}

bool InputManager::isKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, const std::string& name)
{
	if (keyControlMode.empty()) {
		return false;
	}
	return keyControlMode == name && !keyStates[keyCode];
}

bool InputManager::isMousePressed(cocos2d::EventMouse::MouseButton button, const std::string& name)
{
	if (mouseControlMode.empty()) {
		return false;
	}
	return mouseControlMode == name && mouseButtonStates[button];
}

bool InputManager::isMouseReleased(cocos2d::EventMouse::MouseButton button, const std::string& name)
{
	if (mouseControlMode.empty()) {
		return false;
	}
	return mouseControlMode == name && !mouseButtonStates[button];
}

const cocos2d::Vec2* InputManager::getMousePosition(const std::string& name) const
{
	if (mouseControlMode.empty()) {
		return nullptr;
	}
	if (mouseControlMode != name) {
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
