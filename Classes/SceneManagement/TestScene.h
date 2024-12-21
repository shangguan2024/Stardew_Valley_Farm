#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"

class TestScene : public GameScene
{
public:
    static cocos2d::Scene* createScene();

protected:
    void initConstants() override;

private:
    CREATE_FUNC(TestScene);
};

#endif // _FARM_YARD_SCENE_H_
