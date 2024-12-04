/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     HoverButton.cpp
 * File Function: HoverButton类的实现
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#include "HoverButton.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace ui;

HoverButton* HoverButton::create(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage) 
{
    HoverButton* button = new(std::nothrow) HoverButton();
    if (button && button->init(defaultButtonImage, hoverButtonImage, activeButtonImage)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

bool HoverButton::init(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage) 
{
    // 设置图片路径
    this->defaultButtonImage = defaultButtonImage;
    this->hoverButtonImage = hoverButtonImage;
    this->activeButtonImage = activeButtonImage;

    // 初始化 Button
    if (!Button::init(defaultButtonImage, "", "")) {
        return false;
    }

    // 添加鼠标事件监听器
    auto mouseListener = EventListenerMouse::create();

    // 鼠标移动事件
    mouseListener->onMouseMove = CC_CALLBACK_1(HoverButton::onMouseMove, this);

    // 鼠标释放事件
    mouseListener->onMouseUp = CC_CALLBACK_1(HoverButton::onMouseUp, this);

    // 将监听器绑定到当前按钮
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void HoverButton::onMouseMove(Event* event) 
{
    auto mouseEvent = dynamic_cast<EventMouse*>(event);
    if (!mouseEvent) return;

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();
    mousePosition = this->getParent()->convertToNodeSpace(mousePosition);

    // 检查鼠标是否在按钮的范围内
    Rect boundingBox = this->getBoundingBox();
    if (boundingBox.containsPoint(mousePosition)) {
        this->loadTextureNormal(hoverButtonImage); // 切换到悬停图片
    }
    else {
        this->loadTextureNormal(defaultButtonImage); // 恢复默认图片
    }
}

void HoverButton::onMouseUp(Event* event) 
{
    auto mouseEvent = dynamic_cast<EventMouse*>(event);
    if (!mouseEvent) return;

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();
    mousePosition = this->getParent()->convertToNodeSpace(mousePosition);

    // 检查鼠标是否在按钮的范围内
    Rect boundingBox = this->getBoundingBox();
    if (boundingBox.containsPoint(mousePosition)) {
        this->loadTextureNormal(activeButtonImage); // 切换到激活图片
    }
}
