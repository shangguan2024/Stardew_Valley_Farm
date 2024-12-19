#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "cocos2d.h"
#include "HUD.h"
#include "InventoryUI.h"

class UIManager : public cocos2d::Node {
public:
    UIManager();
    virtual ~UIManager();

    // UI 是否激活
    bool isUIActive() const;

    // 创建 UIManager 的实例
    static UIManager* getInstance();

    // 切换 UI 激活状态（例如：打开背包、打开菜单等）
    void toggleUIActiveState(bool active);

    // 回调函数出入栈
    void pushMouseCallbackFunc(std::function<void(cocos2d::Vec2)> callback);
    void popMouseCallBackFunc();

    void showHUD();
    void hideHUD();

    void showInventoryUI();
    void hideInventoryUI();

private:
    // 初始化 UI 管理器
    bool init() override;

    // 注册所有的 UI 监听器（例如键盘、鼠标等）
    void registerUIListeners();

    // 处理键盘按下事件
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 处理键盘释放事件
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 处理鼠标按下事件
    void onMouseDown(cocos2d::Event* event);

    // 处理鼠标释放事件
    void onMouseUp(cocos2d::Event* event);

    // 处理鼠标移动事件
    void onMouseMove(cocos2d::Event* event);

    static UIManager* instance;

    HUD* hud;
    InventoryUI* inventoryUI;

    // 是否处于 UI 激活状态
    bool _isUIActive;

    // UI回调函数
    std::stack<std::function<void(cocos2d::Vec2)>> mouseCallbackfunc;

    // 鼠标位置
    cocos2d::Vec2 _mousePosition;

    // UI 事件监听器
    cocos2d::EventListenerKeyboard* _keyboardListener;
    cocos2d::EventListenerMouse* _mouseListener;
};

#endif // __UI_MANAGER_H__
