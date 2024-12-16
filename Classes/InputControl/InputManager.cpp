#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() :
	keyboardListener(nullptr),
	mouseListener(nullptr),
	mousePosition(cocos2d::Vec2::ZERO)
{
}

InputManager::~InputManager()
{
	// 注销事件监听器
	if (keyboardListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);
	}
	if (mouseListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(mouseListener);
	}
}

bool InputManager::init()
{
	// 注册输入事件
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

void InputManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	// 处理键盘按下事件
	keyStates[keyCode] = true;
	CCLOG("Key pressed: %d", keyCode);
}

void InputManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	// 处理键盘释放事件
	keyStates[keyCode] = false;
	CCLOG("Key released: %d", keyCode);
}

void InputManager::onMouseMove(cocos2d::Event* event)
{
	// 处理鼠标移动事件
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	mousePosition = cocos2d::Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
	CCLOG("Mouse moved to position: (%f, %f)", mouseEvent->getCursorX(), mouseEvent->getCursorY());
}

void InputManager::onMouseDown(cocos2d::Event* event)
{
	// 处理鼠标按下事件
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	mouseButtonStates[mouseEvent->getMouseButton()] = true;
	CCLOG("Mouse button pressed: %d", mouseEvent->getMouseButton());
}

void InputManager::onMouseUp(cocos2d::Event* event)
{
	// 处理鼠标释放事件
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	mouseButtonStates[mouseEvent->getMouseButton()] = false;
	CCLOG("Mouse button released: %d", mouseEvent->getMouseButton());
}

bool InputManager::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	auto it = keyStates.find(keyCode);
	return it != keyStates.end() && it->second;
}

bool InputManager::isKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	auto it = keyStates.find(keyCode);
	return it == keyStates.end() || !it->second;
}

bool InputManager::isMousePressed(cocos2d::EventMouse::MouseButton button)
{
	auto it = mouseButtonStates.find(button);
	return it != mouseButtonStates.end() && it->second;
}

bool InputManager::isMouseReleased(cocos2d::EventMouse::MouseButton button)
{
	auto it = mouseButtonStates.find(button);
	return it == mouseButtonStates.end() || !it->second;
}

cocos2d::Vec2 InputManager::getMousePosition() const
{
	return mousePosition;
}

InputManager* InputManager::getInstance()
{
	if (instance == nullptr) {
		instance = new InputManager();
		instance->init();
	}
	return instance;
}
