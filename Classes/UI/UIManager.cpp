#include "UIManager.h"
#include "cocos2d.h"

UIManager* UIManager::instance = nullptr;

UIManager::UIManager()
	: _isUIActive(false),
	_keyboardListener(nullptr),
	_mouseListener(nullptr),
	_mousePosition(cocos2d::Vec2::ZERO),
	inventoryUI(nullptr)
{
}

UIManager::~UIManager()
{
	// 注销事件监听器
	if (_keyboardListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(_keyboardListener);
	}
	if (_mouseListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(_mouseListener);
	}
}

UIManager* UIManager::getInstance()
{
	if (!instance) {
		instance = new UIManager();
		instance->retain();  // 保证 UIManager 实例不会被销毁
	}
	return instance;
}

bool UIManager::init()
{
	// 注册 UI 事件监听器
	registerUIListeners();
	this->scheduleUpdate();
	return true;
}

void UIManager::registerUIListeners()
{
	// 创建键盘事件监听器
	_keyboardListener = cocos2d::EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(UIManager::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(UIManager::onKeyReleased, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_keyboardListener, 2);

	// 创建鼠标事件监听器
	_mouseListener = cocos2d::EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(UIManager::onMouseDown, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(UIManager::onMouseUp, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(UIManager::onMouseMove, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_mouseListener, 2);
}

void UIManager::toggleUIActiveState(bool active)
{
	_isUIActive = active;
}

void UIManager::showInventoryUI()
{
	if (!inventoryUI) {
		inventoryUI = InventoryUI::create();  // 创建背包UI
		this->addChild(inventoryUI);  // 添加到 UIManager 中
	}
	inventoryUI->setVisible(true);  // 显示背包UI
}

void UIManager::hideInventoryUI()
{
	if (inventoryUI) {
		inventoryUI->setVisible(false);  // 隐藏背包UI
	}
}

bool UIManager::isUIActive() const
{
	return _isUIActive;
}

void UIManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (_isUIActive) {
		CCLOG("UI Key Pressed: %d", keyCode);
		event->stopPropagation();  // 阻止事件继续传播
	}
}

void UIManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (_isUIActive) {
		CCLOG("UI Key Released: %d", keyCode);
		event->stopPropagation();  // 阻止事件继续传播
	}
}

void UIManager::onMouseDown(cocos2d::Event* event)
{
	if (_isUIActive) {
		auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
		_mousePosition = cocos2d::Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
		CCLOG("UI Mouse Down at: (%f, %f)", _mousePosition.x, _mousePosition.y);
		event->stopPropagation();  // 阻止事件继续传播
	}
}

void UIManager::onMouseUp(cocos2d::Event* event)
{
	if (_isUIActive) {
		auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
		CCLOG("UI Mouse Up at: (%f, %f)", mouseEvent->getCursorX(), mouseEvent->getCursorY());
		event->stopPropagation();  // 阻止事件继续传播
	}
}

void UIManager::onMouseMove(cocos2d::Event* event)
{
	if (_isUIActive) {
		auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
		_mousePosition = cocos2d::Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
		CCLOG("UI Mouse Move at: (%f, %f)", _mousePosition.x, _mousePosition.y);
	}
}
