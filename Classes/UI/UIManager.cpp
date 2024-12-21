#include "UIManager.h"

UIManager* UIManager::instance = nullptr;

UIManager::UIManager()
	: _isUIActive(false),
	_keyboardListener(nullptr),
	_mouseListener(nullptr),
	_mousePosition(cocos2d::Vec2::ZERO),
	hud(nullptr),
	inventoryUI(nullptr)
{
}

UIManager::~UIManager()
{
}

UIManager* UIManager::getInstance()
{
	if (!instance) {
		instance = new UIManager();
		instance->retain();  // ��֤ UIManager ʵ�����ᱻ����
		instance->init();
	}
	return instance;
}

bool UIManager::init()
{
	hud = HUD::getInstance();
	this->addChild(hud);
	showHUD();

	return true;
}

void UIManager::registerUIListeners()
{
	// ���������¼�������
	_keyboardListener = cocos2d::EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(UIManager::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(UIManager::onKeyReleased, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_keyboardListener, 2);

	// ��������¼�������
	_mouseListener = cocos2d::EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(UIManager::onMouseDown, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(UIManager::onMouseUp, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(UIManager::onMouseMove, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_mouseListener, 2);
}

void UIManager::unRegisterUIListeners()
{
	// ע���¼�������
	if (_keyboardListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(_keyboardListener);
	}
	if (_mouseListener) {
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(_mouseListener);
	}
}

void UIManager::toggleUIActiveState(bool active)
{
	_isUIActive = active;
}

void UIManager::pushMouseClickCallbackFunc(std::function<void(cocos2d::Vec2)> callback)
{
	mouseClickCallbackFunc.push(callback);
}

void UIManager::popMouseClickCallBackFunc()
{
	if (!mouseClickCallbackFunc.empty()) {
		mouseClickCallbackFunc.pop();
	}
}

void UIManager::pushMouseMoveCallbackFunc(std::function<void(cocos2d::Vec2)> callback)
{
	mouseMoveCallbackFunc.push(callback);
}

void UIManager::popMouseMoveCallBackFunc()
{
	if (!mouseMoveCallbackFunc.empty()) {
		mouseMoveCallbackFunc.pop();
	}
}

void UIManager::showHUD()
{
	hud->toggleVisibility(true);
}

void UIManager::hideHUD()
{
	hud->toggleVisibility(false);
}

void UIManager::showInventoryUI()
{
	if (!inventoryUI) {
		inventoryUI = InventoryUI::create();  // ��������UI
		this->addChild(inventoryUI);  // ��ӵ� UIManager ��
	}
	inventoryUI->setVisible(true);  // ��ʾ����UI
	pushMouseClickCallbackFunc(
		std::function<void(cocos2d::Vec2)>([&](cocos2d::Vec2 position) {
			(inventoryUI->click)(position);  // ���ó�Ա���� click
			})
	);
	pushMouseMoveCallbackFunc(
		std::function<void(cocos2d::Vec2)>([&](cocos2d::Vec2 position) {
			(inventoryUI->attach)(position);  // ���ó�Ա���� attach
			})
	);
	toggleUIActiveState(true);
}

void UIManager::hideInventoryUI()
{
	if (!inventoryUI) {
		CCLOG("UIManager::hideInventoryUI : inventoryUI doesn't exists.");
		return;
	}
	inventoryUI->detach();           // ȡ������
	inventoryUI->setVisible(false);  // ���ر���UI
	popMouseClickCallBackFunc();
	toggleUIActiveState(false);
}

void UIManager::onEnter()
{
	Node::onEnter();

	this->schedule([this](float dt) {
		hud->updateGameTimeHUD();
		}, 1.0f, "Game_time_update_key");

	registerUIListeners();
	this->scheduleUpdate();
}

void UIManager::onExit()
{
	Node::onExit();

	this->unschedule("Game_time_update_key");

	unRegisterUIListeners();
	this->unscheduleUpdate();
}

bool UIManager::isUIActive() const
{
	return _isUIActive;
}

void UIManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (_isUIActive) {
		CCLOG("UI Key Pressed: %d", keyCode);
		event->stopPropagation();  // ��ֹ�¼���������
	}
}

void UIManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (_isUIActive) {
		CCLOG("UI Key Released: %d", keyCode);
		event->stopPropagation();  // ��ֹ�¼���������
	}
}

void UIManager::onMouseDown(cocos2d::Event* event)
{
	if (_isUIActive) {
		auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
		_mousePosition = cocos2d::Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
		if (!mouseClickCallbackFunc.empty()) {
			mouseClickCallbackFunc.top()(_mousePosition);
		}
		CCLOG("UI Mouse Down at: (%f, %f)", _mousePosition.x, _mousePosition.y);
		event->stopPropagation();  // ��ֹ�¼���������
	}
}

void UIManager::onMouseUp(cocos2d::Event* event)
{
	if (_isUIActive) {
		auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
		CCLOG("UI Mouse Up at: (%f, %f)", mouseEvent->getCursorX(), mouseEvent->getCursorY());
		event->stopPropagation();  // ��ֹ�¼���������
	}
}

void UIManager::onMouseMove(cocos2d::Event* event)
{
	if (_isUIActive) {
		auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
		_mousePosition = cocos2d::Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
		if (!mouseMoveCallbackFunc.empty()) {
			mouseMoveCallbackFunc.top()(_mousePosition);
		}
		// CCLOG("UI Mouse Move at: (%f, %f)", _mousePosition.x, _mousePosition.y);
	}
}
