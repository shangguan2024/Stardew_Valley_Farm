// HUD.h
#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include "HoverButton.h"

class HUD : public cocos2d::Layer {
public:
    HUD();
    ~HUD();

    static HUD* getInstance();

    bool init() override;

    // 更新 HUD 内容
    void updateHUD(float health, int score);

    // 显示/隐藏 HUD
    void toggleVisibility(bool visible);

private:
    static HUD* create();

    static HUD* instance;

    cocos2d::ProgressTimer* _healthBar;
    cocos2d::Label* _scoreLabel;
};

#endif // __HUD_H__
