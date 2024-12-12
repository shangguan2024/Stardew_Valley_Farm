/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTime.cpp
 * File Function: GameTime类的实现
 * Author:        张翔
 * Update Date:   2024/12/13
 ****************************************************************/

#include "GameTime.h"
#include "cocos2d.h"

 // 静态实例初始化
GameTime* GameTime::instance = nullptr;

 // 获取单例实例
GameTime* GameTime::getInstance()
{
	if (instance == nullptr) {
		// 使用 nothrow 分配内存
		instance = new (std::nothrow) GameTime();
		// 初始化失败则销毁实例
		if (!instance) {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

GameTime::GameTime(int y = 2024, int m = 1, int d = 1, int h = 0, int min = 0, double speed = 1.0) :year(y), month(m), day(d), hour(h), minute(min), timeSpeed(speed), running(false)
{
	normalize();
}

void GameTime::normalize()
{

}

void GameTime::updateLoop()
{
	while (running) {
		// 更新间隔
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		// 添加时间
		addSeconds(1); 
	}
}

void GameTime::setTimeSpeed(double speed)
{
	timeSpeed = speed;
}

void GameTime::start()
{
	running = true;
	std::thread(&GameTime::updateLoop, this).detach();
}

void GameTime::stop()
{
	running = false;
}

void GameTime::addSeconds(int realMinutes)
{
	int gameMinutes = static_cast<int>(realMinutes * timeSpeed);
	minute += gameMinutes;
	normalize();
}

std::string GameTime::toString() const
{

}
