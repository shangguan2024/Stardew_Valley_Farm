/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     UiLayer.h
 * File Function: UiLayer类的定义
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#ifndef _UI_LAYER_
#define _UI_LAYER_

#include "cocos2d.h"

class UiLayer :cocos2d::Layer 
{
public:
    // 创建一个 UiLayer 实例
    static UiLayer* createLayer();

    // 初始化方法
    virtual bool init();

    // 更新方法
    void update(float delta);

    // 定义宏
    CREATE_FUNC(UiLayer);

private:

    

};

#endif // _UI_LAYER_

