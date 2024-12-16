#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"

class InputManager : public cocos2d::Node {
public:
    InputManager();
    virtual ~InputManager();

    bool init();  // 返回bool值，指示是否初始化成功

    void registerEventListeners();

    // 事件回调函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void onMouseMove(cocos2d::Event* event);
    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);

    // 获取输入状态
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
    bool isKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

    bool isMousePressed(cocos2d::EventMouse::MouseButton button);
    bool isMouseReleased(cocos2d::EventMouse::MouseButton button);
    cocos2d::Vec2 getMousePosition() const;

    static InputManager* getInstance();

private:
    static InputManager* instance;

    // 事件监听器
    cocos2d::EventListenerKeyboard* keyboardListener;
    cocos2d::EventListenerMouse* mouseListener;

    std::unordered_map<cocos2d::EventKeyboard::KeyCode, bool> keyStates;
    std::unordered_map<cocos2d::EventMouse::MouseButton, bool> mouseButtonStates;
    cocos2d::Vec2 mousePosition;  // 鼠标位置
};

#endif // __INPUT_MANAGER_H__
