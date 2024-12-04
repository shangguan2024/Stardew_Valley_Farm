/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.h
 * File Function: FarmYardScene类的定义
 * Author:        刘逸飞
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef _FARM_YARD_SCENE_H_
#define _FARM_YARD_SCENE_H_

#include "cocos2d.h"
#include "Scene/MenuScene.h"
#include "Scene/BackgroundTiledMap.h"
#include "Player/Player.h"
/****************************************************
 * FarmYardScene类
 * 一个大的Scene场景，供其他Yard场景元素调用
*****************************************************/
class FarmYardScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // 每一帧被自动调用的 update 方法
    virtual void update(float delta);
    CREATE_FUNC(FarmYardScene);

private:

};

/****************************************************
 * FarmYardBackground类
 * 农场的瓦片地图 跟MapBg区分开是为了做耕种等等的操作
*****************************************************/
class FarmYardBackground : public MapBg 
{
public:
    std::string files_name = "TiledMap/Farm_map_simple.tmx";

    bool init();
    static MapBg* createMap();

    void getlayer();

    void setlayer();
};
#endif // _FARM_YARD_SCENE_H_