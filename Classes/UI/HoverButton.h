#ifndef _HOVER_BUTTON_H_
#define _HOVER_BUTTON_H_

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HoverButton : public cocos2d::ui::Button
{
public:
    static HoverButton *create(const std::string &defaultButtonImage, const std::string &hoverButtonImage, const std::string &activeButtonImage);

    bool init(const std::string &defaultButtonImage, const std::string &hoverButtonImage, const std::string &activeButtonImage);

private:
    std::string defaultButtonImage;
    std::string hoverButtonImage;
    std::string activeButtonImage;

    void onMouseMove(cocos2d::Event *event);

    void onMouseUp(cocos2d::Event *event);
};

#endif // _HOVER_BUTTON_H_
