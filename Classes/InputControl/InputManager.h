#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"

class InputManager : public cocos2d::Node {
public:
    InputManager();
    virtual ~InputManager();

    bool init();  // ����boolֵ��ָʾ�Ƿ��ʼ���ɹ�

    void registerEventListeners();

    // �¼��ص�����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void onMouseMove(cocos2d::Event* event);
    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);

    // ��ȡ����״̬
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
    bool isKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

    bool isMousePressed(cocos2d::EventMouse::MouseButton button);
    bool isMouseReleased(cocos2d::EventMouse::MouseButton button);
    cocos2d::Vec2 getMousePosition() const;

    static InputManager* getInstance();

private:
    static InputManager* instance;

    // �¼�������
    cocos2d::EventListenerKeyboard* keyboardListener;
    cocos2d::EventListenerMouse* mouseListener;

    std::unordered_map<cocos2d::EventKeyboard::KeyCode, bool> keyStates;
    std::unordered_map<cocos2d::EventMouse::MouseButton, bool> mouseButtonStates;
    cocos2d::Vec2 mousePosition;  // ���λ��
};

#endif // __INPUT_MANAGER_H__
