#ifndef __BEACH_SCENE_H__
#define __BEACH_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"

class BeachScene : public GameScene
{
public:
    static cocos2d::Scene* createScene();

protected:
    void initConstants() override;

private:
    CREATE_FUNC(BeachScene);
};

#endif // _FARM_YARD_SCENE_H_
