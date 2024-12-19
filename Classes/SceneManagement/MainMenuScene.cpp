#include "SceneManager.h"
#include "MainMenuScene.h"
#include "UI/HoverButton.h"
#include "FarmYardScene.h"
// #include "../Music/AudioPlayer.h"
#include "ResourceManagement/Constant.h"

USING_NS_CC;

// ��������
Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

// ��ʼ������
bool MainMenuScene::init()
{
	// ��������
	if (!Scene::init()) {
		return false;
	}

	// ���ر���
	const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
	const auto background = Sprite::create("Scenes/MenuScene.png");
	background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	this->addChild(background);

	// ������ť
	auto newGameButton = HoverButton::create("UI/Buttons/CreateButton.png",
		"UI/Buttons/CreateButton.png",
		"UI/Buttons/CreateButton.png");
	auto loadGameButton = HoverButton::create("UI/Buttons/LoadButton.png",
		"UI/Buttons/LoadButton.png",
		"UI/Buttons/LoadButton.png");
	auto exitGameButton = HoverButton::create("UI/Buttons/ExitButton.png",
		"UI/Buttons/ExitButton.png",
		"UI/Buttons/ExitButton.png");

	// ���ð�ťλ��
	newGameButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_NEW_GAME_BUTTON_OFFSET_X, screenSize.height / 2 + MENU_SCENE_BUTTONS_OFFSET_Y));
	loadGameButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_LOAD_GAME_BUTTON_OFFSET_X, screenSize.height / 2 + MENU_SCENE_BUTTONS_OFFSET_Y));
	exitGameButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X, screenSize.height / 2 + MENU_SCENE_BUTTONS_OFFSET_Y));

	// Ϊ��ť����¼�������
	newGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
			auto scene = FarmYardScene::createScene();
			SceneManager::setSceneTransition(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, scene, cocos2d::Color3B::WHITE));
			SceneManager::switchToScene(scene);
		} });
		loadGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
			if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {

			} });
			exitGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
				if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
					Director::getInstance()->end();
				} });

				// ����ť���볡��
				this->addChild(newGameButton);
				this->addChild(loadGameButton);
				this->addChild(exitGameButton);

				return true;
}
