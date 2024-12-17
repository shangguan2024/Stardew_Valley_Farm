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
	// ע���¼�������
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
		instance->retain();  // ��֤ UIManager ʵ�����ᱻ����
	}
	return instance;
}

bool UIManager::init()
{
	// ע�� UI �¼�������
	registerUIListeners();
	this->scheduleUpdate();
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

void UIManager::toggleUIActiveState(bool active)
{
	_isUIActive = active;
}

void UIManager::showInventoryUI()
{
	if (!inventoryUI) {
		inventoryUI = InventoryUI::create();  // ��������UI
		this->addChild(inventoryUI);  // ��ӵ� UIManager ��
	}
	inventoryUI->setVisible(true);  // ��ʾ����UI
}

void UIManager::hideInventoryUI()
{
	if (inventoryUI) {
		inventoryUI->setVisible(false);  // ���ر���UI
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
		CCLOG("UI Mouse Move at: (%f, %f)", _mousePosition.x, _mousePosition.y);
	}
}
