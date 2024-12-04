#pragma once
/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     BackgroundTiledMap.h
 * File Function: MapBg类的定义 以其形成瓦片地图
 * Author:        
 * Update Date:   2024/12/3
 ****************************************************************/

#include "cocos2d.h"

 /************
  * MapBg类
  * 在Scene场景中创建瓦片地图
 *
 *************/
class MapBg : public cocos2d::Sprite
{
public:
    bool init();
    static MapBg* create();
    //加载并形成TMX瓦片地图 map_name需要包含相对路径
    bool LoadTMXMap(std::string map_name);

};

