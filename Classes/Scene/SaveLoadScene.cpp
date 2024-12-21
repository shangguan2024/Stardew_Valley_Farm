/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     SaveLoadScene.h
 * File Function: SaveLoadScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/22
 ****************************************************************/

#include "SaveLoadScene.h"

USING_NS_CC;

Scene* SaveLoadScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SaveLoadScene::create();
    scene->addChild(layer);
    return scene;
}

bool SaveLoadScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("Scenes/SaveLoadScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);



}