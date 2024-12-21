#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "cocos2d.h"
#include "HUD.h"
#include "InventoryUI.h"

class UIManager : public cocos2d::Node {
public:
	UIManager();
	virtual ~UIManager();

	// UI �Ƿ񼤻�
	bool isUIActive() const;

	// ���� UIManager ��ʵ��
	static UIManager* getInstance();

	// �л� UI ����״̬�����磺�򿪱������򿪲˵��ȣ�
	void toggleUIActiveState(bool active);

	// �ص���������ջ
	void pushMouseClickCallbackFunc(std::function<void(cocos2d::Vec2)> callback);
	void popMouseClickCallBackFunc();
	void pushMouseMoveCallbackFunc(std::function<void(cocos2d::Vec2)> callback);
	void popMouseMoveCallBackFunc();

	void showHUD();
	void hideHUD();

	void showInventoryUI();
	void hideInventoryUI();

protected:
	void onEnter() override;
	void onExit() override;

private:
	// ��ʼ�� UI ������
	bool init() override;

	// ע�����е� UI ��������������̡����ȣ�
	void registerUIListeners();
	void unRegisterUIListeners();

	// �������̰����¼�
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// ���������ͷ��¼�
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// ������갴���¼�
	void onMouseDown(cocos2d::Event* event);

	// ��������ͷ��¼�
	void onMouseUp(cocos2d::Event* event);

	// ��������ƶ��¼�
	void onMouseMove(cocos2d::Event* event);

	static UIManager* instance;

	HUD* hud;
	InventoryUI* inventoryUI;

	// �Ƿ��� UI ����״̬
	bool _isUIActive;

	// UI�ص�����
	std::stack<std::function<void(cocos2d::Vec2)>> mouseClickCallbackFunc;
	std::stack<std::function<void(cocos2d::Vec2)>> mouseMoveCallbackFunc;

	// ���λ��
	cocos2d::Vec2 _mousePosition;

	// UI �¼�������
	cocos2d::EventListenerKeyboard* _keyboardListener;
	cocos2d::EventListenerMouse* _mouseListener;
};

#endif // __UI_MANAGER_H__