#ifndef __BEACH_H__
#define __BEACH_H__

#include "cocos2d.h"
#include "GameScene.h"

class Beach : public GameScene
{
public:
    static cocos2d::Scene* createScene();

protected:
    void initConstants() override;

private:
    CREATE_FUNC(Beach);
};

#endif // _FARM_YARD_SCENE_H_
