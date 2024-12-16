#include "HoverButton.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace ui;

HoverButton *HoverButton::create(const std::string &defaultButtonImage, const std::string &hoverButtonImage, const std::string &activeButtonImage)
{
    HoverButton *button = new (std::nothrow) HoverButton();
    if (button && button->init(defaultButtonImage, hoverButtonImage, activeButtonImage))
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

bool HoverButton::init(const std::string &defaultButtonImage, const std::string &hoverButtonImage, const std::string &activeButtonImage)
{
    this->defaultButtonImage = defaultButtonImage;
    this->hoverButtonImage = hoverButtonImage;
    this->activeButtonImage = activeButtonImage;

    if (!Button::init(defaultButtonImage, "", ""))
    {
        return false;
    }

    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseMove = CC_CALLBACK_1(HoverButton::onMouseMove, this);

    mouseListener->onMouseUp = CC_CALLBACK_1(HoverButton::onMouseUp, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void HoverButton::onMouseMove(Event *event)
{
    auto mouseEvent = dynamic_cast<EventMouse *>(event);
    if (!mouseEvent)
        return;

    Vec2 mousePosition = mouseEvent->getLocationInView();
    mousePosition = this->getParent()->convertToNodeSpace(mousePosition);

    Rect boundingBox = this->getBoundingBox();
    if (boundingBox.containsPoint(mousePosition))
    {
        loadTextureNormal(hoverButtonImage);
    }
    else
    {
        loadTextureNormal(defaultButtonImage);
    }
}

void HoverButton::onMouseUp(Event *event)
{
    auto mouseEvent = dynamic_cast<EventMouse *>(event);
    if (!mouseEvent)
        return;

    Vec2 mousePosition = mouseEvent->getLocationInView();
    mousePosition = this->getParent()->convertToNodeSpace(mousePosition);

    Rect boundingBox = this->getBoundingBox();
    if (boundingBox.containsPoint(mousePosition))
    {
        this->loadTextureNormal(activeButtonImage);
    }
}
