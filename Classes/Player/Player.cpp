<<<<<<< Updated upstream
#include "Player.h"

USING_NS_CC;

PlayerPosition* PlayerPosition::create(float pos_x, float pos_y)
{
	PlayerPosition* tp = new PlayerPosition(pos_x, pos_y);
	if (tp && tp->init()) 
	{
		tp->autorelease();
		return tp;
	}
	else 
	{
		CC_SAFE_DELETE(tp);
	}
	return nullptr;
}

bool PlayerPosition::IsKeyPressed(EventKeyboard::KeyCode keyCode)
{
	if (keys[keyCode])
		return true;
	else
		return false;
}

void PlayerPosition::KeyPressedDuration(EventKeyboard::KeyCode keyCode) 
{
	int offsetX = 0, offsetY = 0;
	switch (keyCode) 
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			offsetX = -5;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			offsetX = 5;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			offsetY = 5;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			offsetY = -5;
			break;
		default:
			offsetY = offsetX = 0;
			break;
	}
	p_x_speed = offsetX;
	p_y_speed = offsetY;
	
	}

bool PlayerPosition::init() 
{
	if (!Sprite::init()) 
	{
		return false;
	}

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			keys[keyCode] = true;
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			keys[keyCode] = false;
		};
	Texture2D* tex = Director::getInstance()->getTextureCache()->addImage("PlayerImage/player_01.png");

	SpriteFrame* tframe;
	char* tname;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) 
		{
			tname = new char[10];
			sprintf(tname, "role_0%d", 4 * i + (j + 1));
			tframe = SpriteFrame::createWithTexture(tex, Rect(32 * j, 48 * i, 32, 48));
			SpriteFrameCache::getInstance()->addSpriteFrame(tframe, tname);
		}
	}

	if (Sprite::initWithSpriteFrameName("role_01"))
	{
		this->scheduleUpdate();
		return true;
	}

	return true;
}

void PlayerPosition::update(float dt) 
{
	Sprite::update(dt);
	timelast += dt;
	if (IsKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		KeyPressedDuration((EventKeyboard::KeyCode::KEY_LEFT_ARROW));
		p_direction = 2;
	}
	else if (IsKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		KeyPressedDuration((EventKeyboard::KeyCode::KEY_RIGHT_ARROW));
		p_direction = 3;
	}
	else if (IsKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
	{
		KeyPressedDuration((EventKeyboard::KeyCode::KEY_UP_ARROW));
		p_direction = 4;
	}
	else if (IsKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
	{
		KeyPressedDuration((EventKeyboard::KeyCode::KEY_DOWN_ARROW));
		p_direction = 1;
	}

	if (timelast > 0.2f)
	{
		timelast -= 0.2f;
		++p_currentFrame;
		if (p_currentFrame > 4)
		{
			p_currentFrame = 1;
		}
		updateViewByCurrentFrame();
	}

	float target_x = p_x + p_x_speed;
	float target_y = p_y + p_y_speed;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (target_x >= 0 && target_x <= visibleSize.width && target_y >= 0 && target_y <= visibleSize.height)//��������Ļ��Χ��
	{
		this->setPosition(target_x, target_y);
		
		p_x = target_x;
		p_y = target_y;
	}
	p_x_speed = 0;
	p_y_speed = 0;

}

void PlayerPosition::updateViewByCurrentFrame() 
{
	if (p_x_speed == 0 && p_y_speed == 0) 
	{
		return;
	}
	char* texName = new char[10];
	sprintf(texName, "role_0%d", p_currentFrame + (p_direction - 1) * 4);
	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(texName));
	delete texName;
}
=======
/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Player.cpp
 * File Function: Player类的实现
 * Author:        
 * Update Date:   2024/12/4
 ****************************************************************/

#include "Player.h"

>>>>>>> Stashed changes
