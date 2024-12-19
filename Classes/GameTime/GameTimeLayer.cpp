/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTimeLayer.cpp
 * File Function: GameTimeLayer类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "GameTimeLayer.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

bool GameTimeLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	// 设置时间显示背景
	timeIcon = Sprite::create("defaulthead.png");
	timeIcon->setPosition(Vec2(50, 50));  // 固定图标位置
	this->addChild(timeIcon);

	// 设置时间

	// 每秒更新一次时间
	this->schedule([this](float deltaTime) {
		updateTime(deltaTime);
		}, 1.0f, "update_time_key");

	return true;
}

void GameTimeLayer::updateTime(float delta)
{
	// 更新 timeLabel
}

#if 0
 
GameTimeLayer* GameTimeLayer::getInstance()
{
	if (instance == nullptr) {
		// 使用 nothrow 分配内存
		instance = new (std::nothrow) GameTimeLayer();
		// 初始化失败则销毁实例
		if (!instance) {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

void GameTimeLayer::GameTimeLayerUpdate(Camera* camera) 
{
	// 更新时间显示
	clean("timelabel");
	gametime = GameTime::getInstance();
	timeLabel = Label::createWithSystemFont(gametime->toString(), "Arial", 30);
	float cameraWidth = Director::getInstance()->getVisibleSize().width * (camera->getPosition3D().z / DEFAULT_VIEW_HEIGHT);
	float cameraHeight = Director::getInstance()->getVisibleSize().height * (camera->getPosition3D().z / DEFAULT_VIEW_HEIGHT);
	timeLabel->setPosition(camera->getPosition() + Vec2(240, 180) * (camera->getPosition3D().z / DEFAULT_VIEW_HEIGHT));
	this->addChild(timeLabel, 10, "timelabel");
	timeLabel->setCameraMask(unsigned short(CameraFlag::USER1));

	// 添加时间显示的背景
	clean("layercolor");
	layercolor = LayerColor::create(Color4B(0, 255, 0, 128));
	layercolor->setContentSize(Size(timeLabel->getContentSize().width, timeLabel->getContentSize().height + 5));
	layercolor->setAnchorPoint(Vec2(0, 0));
	layercolor->setPosition(timeLabel->getPosition() - timeLabel->getContentSize() / 2);
	this->addChild(layercolor, 8, "layercolor");
	layercolor->setCameraMask(unsigned short(CameraFlag::USER1));
	// 添加时间显示的外框
	clean("sprite");
	sprite = Sprite::create("chatBox.png");
	sprite->setContentSize(layercolor->getContentSize());
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(timeLabel->getPosition() - timeLabel->getContentSize() / 2);
	this->addChild(sprite, 9, "sprite");
	sprite->setCameraMask(unsigned short(CameraFlag::USER1));
}

void GameTimeLayer::clean(std::string name) 
{
	auto removelabel = this->getChildByName(name);
	if (removelabel != nullptr)
	{
		removelabel->removeFromParentAndCleanup(true);
	}
}

#endif
