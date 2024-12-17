#include "SceneManager.h"
#include "MainMenuScene.h"
#include "../UI/HoverButton.h"
#include "FarmYardScene.h"
// #include "../Music/AudioPlayer.h"
#include "ResourceManagement/Constant.h"

USING_NS_CC;

// 创建场景
Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

// 初始化场景
bool MainMenuScene::init()
{
	// 创建场景
	if (!Scene::init()) {
		return false;
	}

	// 加载背景
	const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
	const auto background = Sprite::create("Scenes/MenuScene.png");
	background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	this->addChild(background);

	// 创建按钮
	auto newGameButton = HoverButton::create("Buttons/MenuSceneButtons/CreateButton.png",
		"Buttons/MenuSceneButtons/CreateButton.png",
		"Buttons/MenuSceneButtons/CreateButton.png");
	auto loadGameButton = HoverButton::create("Buttons/MenuSceneButtons/LoadButton.png",
		"Buttons/MenuSceneButtons/LoadButton.png",
		"Buttons/MenuSceneButtons/LoadButton.png");
	auto exitGameButton = HoverButton::create("Buttons/MenuSceneButtons/ExitButton.png",
		"Buttons/MenuSceneButtons/ExitButton.png",
		"Buttons/MenuSceneButtons/ExitButton.png");

	// 设置按钮位置
	newGameButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_NEW_GAME_BUTTON_OFFSET_X, screenSize.height / 2 + MENU_SCENE_BUTTONS_OFFSET_Y));
	loadGameButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_LOAD_GAME_BUTTON_OFFSET_X, screenSize.height / 2 + MENU_SCENE_BUTTONS_OFFSET_Y));
	exitGameButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X, screenSize.height / 2 + MENU_SCENE_BUTTONS_OFFSET_Y));

	// 为按钮添加事件处理器
	newGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
			// Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, FarmYardScene::createScene(), cocos2d::Color3B::WHITE));
			auto scene = FarmYardScene::createScene();
			SceneManager::setSceneTransition(cocos2d::TransitionFade::create(1.0f, scene));
			SceneManager::switchToScene(scene);
		}
		});
	loadGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {

		}
		});
	exitGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
			Director::getInstance()->end();
		}
		});

	// 将按钮加入场景
	this->addChild(newGameButton);
	this->addChild(loadGameButton);
	this->addChild(exitGameButton);

	return true;
}