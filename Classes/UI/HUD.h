// HUD.h
#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include "HoverButton.h"

class HUD : public cocos2d::Layer {
public:
    HUD();
    ~HUD();

    static HUD* create();

    bool init() override;

    // 更新 HUD 内容
    void updateHUD(float health, int score);

    // 显示/隐藏 HUD
    void toggleVisibility(bool visible);

private:
    cocos2d::ProgressTimer* _healthBar;
    cocos2d::Label* _scoreLabel;
    HoverButton* _hoverButton;

    void onButtonHover(cocos2d::Event* event);
    void onButtonClick(cocos2d::Ref* sender);
};

#endif // __HUD_H__
