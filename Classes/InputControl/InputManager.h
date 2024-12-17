#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"

class InputManager : public cocos2d::Node {
public:
	InputManager();
	virtual ~InputManager();

	bool init();  // ����boolֵ��ָʾ�Ƿ��ʼ���ɹ�

	void registerEventListeners();

	// ע��ص�����
	void registerKeyCallbackFunc(KeyControlMode mode, std::function<void(cocos2d::EventKeyboard::KeyCode)> callback);
	void registerMouseCallbackFunc(MouseControlMode mode, std::function<void(cocos2d::EventMouse::MouseButton)> callback);

	// �¼��ص�����
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);

	// ��������״̬
	void setCurrentKeyControlMode(KeyControlMode mode);
	void setCurrentMouseControlMode(MouseControlMode mode);
	void popCurrentKeyControlMode();
	void popCurrentMouseControlMode();

	// ��ȡ����״̬(polling)
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, KeyControlMode mode);
	bool isKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, KeyControlMode mode);

	bool isMousePressed(cocos2d::EventMouse::MouseButton button, MouseControlMode mode);
	bool isMouseReleased(cocos2d::EventMouse::MouseButton button, MouseControlMode mode);
	const cocos2d::Vec2* getMousePosition(MouseControlMode mode) const;

	static InputManager* getInstance();

private:
	static InputManager* instance;

	// �¼�������
	cocos2d::EventListenerKeyboard* keyboardListener;
	cocos2d::EventListenerMouse* mouseListener;

	std::stack<KeyControlMode> keyControlMode;
	std::stack<MouseControlMode> mouseControlMode;

	// polling
	std::unordered_map<cocos2d::EventKeyboard::KeyCode, bool> keyStates;
	std::unordered_map<cocos2d::EventMouse::MouseButton, bool> mouseButtonStates;
	cocos2d::Vec2 mousePosition;

	// �ص�
	std::unordered_map<KeyControlMode,std::function<void(cocos2d::EventKeyboard::KeyCode)>> keyCallbackFuncs;
	std::unordered_map<MouseControlMode,std::function<void(cocos2d::EventMouse::MouseButton)>> mouseCallbackFuncs;
};

#endif // __INPUT_MANAGER_H__
