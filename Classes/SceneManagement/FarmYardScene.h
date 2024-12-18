/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.h
 * File Function: FarmYardScene类的定义
 * Author:        张翔
 * Update Date:   2024/12/5
 ****************************************************************/

#ifndef _FARM_YARD_SCENE_H_
#define _FARM_YARD_SCENE_H_

#include "cocos2d.h"
#include "GameScene.h"

class FarmYardScene : public GameScene
{
public:
    static cocos2d::Scene* createScene();

protected:
    void initConstants() override;

private:
    // 实现 FarmYardScene 类的 create 方法
    CREATE_FUNC(FarmYardScene);
};

#endif // _FARM_YARD_SCENE_H_
