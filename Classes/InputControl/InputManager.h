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
	void unRegisterEventListeners();

	// 注册回调函数
	void registerKeyCallbackFunc(const std::string & name, std::function<void(cocos2d::EventKeyboard::KeyCode)> callback);
	void registerMouseCallbackFunc(const std::string & name, std::function<void(cocos2d::EventMouse::MouseButton)> callback);

	// 事件回调函数
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);

	// 控制输入状态
	void setCurrentKeyControlMode(const std::string & name);
	void setCurrentMouseControlMode(const std::string & name);
	void resetCurrentKeyControlMode(const std::string& name);
	void resetCurrentMouseControlMode(const std::string& name);

	// 获取输入状态(polling)
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, const std::string & name);
	bool isKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, const std::string& name);

	bool isMousePressed(cocos2d::EventMouse::MouseButton button, const std::string& name);
	bool isMouseReleased(cocos2d::EventMouse::MouseButton button, const std::string& name);
	const cocos2d::Vec2 * getMousePosition(const std::string& name) const;

	void clearPollingStates();

	static InputManager* getInstance();

private:
	static InputManager* instance;

	// 事件监听器
	cocos2d::EventListenerKeyboard* keyboardListener;
	cocos2d::EventListenerMouse* mouseListener;

	std::string keyControlMode;
	std::string mouseControlMode;

	// polling
	std::unordered_map<cocos2d::EventKeyboard::KeyCode, bool> keyStates;
	std::unordered_map<cocos2d::EventMouse::MouseButton, bool> mouseButtonStates;
	cocos2d::Vec2 mousePosition;

	// 回调
	std::unordered_map<std::string,std::function<void(cocos2d::EventKeyboard::KeyCode)>> keyCallbackFuncs;
	std::unordered_map<std::string,std::function<void(cocos2d::EventMouse::MouseButton)>> mouseCallbackFuncs;
};

#endif // __INPUT_MANAGER_H__
