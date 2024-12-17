#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"

class InputManager : public cocos2d::Node {
public:
	InputManager();
	virtual ~InputManager();

	bool init();  // 返回bool值，指示是否初始化成功

	void registerEventListeners();

	// 注册回调函数
	void registerKeyCallbackFunc(KeyControlMode mode, std::function<void(cocos2d::EventKeyboard::KeyCode)> callback);
	void registerMouseCallbackFunc(MouseControlMode mode, std::function<void(cocos2d::EventMouse::MouseButton)> callback);

	// 事件回调函数
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);

	// 控制输入状态
	void setCurrentKeyControlMode(KeyControlMode mode);
	void setCurrentMouseControlMode(MouseControlMode mode);
	void popCurrentKeyControlMode();
	void popCurrentMouseControlMode();

	// 获取输入状态(polling)
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, KeyControlMode mode);
	bool isKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, KeyControlMode mode);

	bool isMousePressed(cocos2d::EventMouse::MouseButton button, MouseControlMode mode);
	bool isMouseReleased(cocos2d::EventMouse::MouseButton button, MouseControlMode mode);
	const cocos2d::Vec2* getMousePosition(MouseControlMode mode) const;

	static InputManager* getInstance();

private:
	static InputManager* instance;

	// 事件监听器
	cocos2d::EventListenerKeyboard* keyboardListener;
	cocos2d::EventListenerMouse* mouseListener;

	std::stack<KeyControlMode> keyControlMode;
	std::stack<MouseControlMode> mouseControlMode;

	// polling
	std::unordered_map<cocos2d::EventKeyboard::KeyCode, bool> keyStates;
	std::unordered_map<cocos2d::EventMouse::MouseButton, bool> mouseButtonStates;
	cocos2d::Vec2 mousePosition;

	// 回调
	std::unordered_map<KeyControlMode,std::function<void(cocos2d::EventKeyboard::KeyCode)>> keyCallbackFuncs;
	std::unordered_map<MouseControlMode,std::function<void(cocos2d::EventMouse::MouseButton)>> mouseCallbackFuncs;
};

#endif // __INPUT_MANAGER_H__
