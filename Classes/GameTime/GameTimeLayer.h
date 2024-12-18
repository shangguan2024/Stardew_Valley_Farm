#pragma once
#include "cocos2d.h"
#include "../GameTime/GameTime.h"

class GameTimeLayer :public cocos2d::Layer
{
private:
	// ¾²Ì¬ÊµÀýÖ¸Õë
	static GameTimeLayer* instance;
public:
	GameTime* gametime;
	cocos2d::Label* timeLabel;
	cocos2d::LayerColor* layercolor;
	cocos2d::Sprite* sprite;

	GameTimeLayer();

	static GameTimeLayer* getInstance();

	void GameTimeLayerUpdate(cocos2d::Camera* camera);

	void clean(std::string name);
};