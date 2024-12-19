#ifndef __FARM_YARD_H__
#define __FARM_YARD_H__

#include "cocos2d.h"
#include "GameScene.h"

class FarmYard : public GameScene
{
public:
    static cocos2d::Scene* createScene();

protected:
    void initConstants() override;

private:
    CREATE_FUNC(FarmYard);
};

#endif // _FARM_YARD_SCENE_H_
