// HUD.h
#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include "GameTime/GameTime.h"

class HUD : public cocos2d::Layer {
public:
    HUD();
    ~HUD();

    static HUD* getInstance();

    bool init() override;

    // 更新 HUD 内容
    void updateStrengthBarHUD();

    // 显示/隐藏 HUD
    void toggleVisibility(bool visible);

private:
    static HUD* create();

    static HUD* instance;

    // 更新 HUD 内容
    void updateGameTimeHUD();

    GameTime* gameTime;
    cocos2d::Label* gameTimeLabel;

    cocos2d::ProgressTimer* strengthBar;
    cocos2d::Label* strengthLabel;
};

#endif // __HUD_H__
