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

    // ���� HUD ����
    void updateStrengthBarHUD();

    // ��ʾ/���� HUD
    void toggleVisibility(bool visible);

private:
    static HUD* create();

    static HUD* instance;

    // ���� HUD ����
    void updateGameTimeHUD();

    GameTime* gameTime;
    cocos2d::Label* gameTimeLabel;

    cocos2d::ProgressTimer* strengthBar;
    cocos2d::Label* strengthLabel;
};

#endif // __HUD_H__
