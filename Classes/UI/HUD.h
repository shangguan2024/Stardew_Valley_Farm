// HUD.h
#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include "GameTime/GameTime.h"
#include "ResourceManagement/ResourceManager.h"

class HUD : public cocos2d::Layer {
public:
    HUD();
    ~HUD();

    static HUD* getInstance();

    bool init() override;
    void start();

    // 更新 HUD 内容
    void updateStrengthBarHUD();
    void updateGameTimeHUD();

    // 显示/隐藏 HUD
    void toggleVisibility(bool visible);

private:
    static HUD* create();

    static HUD* instance;

    static ResourceManager* resourceManager;


    GameTime* gameTime;
    cocos2d::Label* gameTimeLabel;

    cocos2d::ProgressTimer* energyBar;
    cocos2d::Label* energyLabel;
};

#endif // __HUD_H__
