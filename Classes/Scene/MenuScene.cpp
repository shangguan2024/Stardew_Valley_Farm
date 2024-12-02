#include "MenuScene.h"
#include "Button/HoverButton.h"

USING_NS_CC;

// 创建场景
Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool MenuScene::init()
{
    // 创建场景
    if (!Scene::init()){
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/MenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto newGameButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/CreateButton.png",
        "../Resources/Buttons/MenuSceneButtons/CreateButton.png",
        "../Resources/Buttons/MenuSceneButtons/CreateButton.png");
    auto loadGameButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/ExitButton.png",
        "../Resources/Buttons/MenuSceneButtons/ExitButton.png",
        "../Resources/Buttons/MenuSceneButtons/ExitButton.png");
    auto exitGameButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/LoadButton.png",
        "../Resources/Buttons/MenuSceneButtons/LoadButton.png",
        "../Resources/Buttons/MenuSceneButtons/LoadButton.png");



    this->addChild(newGameButton);
    this->addChild(loadGameButton);
    this->addChild(exitGameButton);

    return true;
}

