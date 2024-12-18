/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTime.h
 * File Function: GameTime类的定义
 * Author:        lyf
 * Update Date:   2024/12/13
 ****************************************************************/

#ifndef _GAME_TIME_H_
#define _GAME_TIME_H_

#include <chrono>
#include <thread>
#include <mutex>

class GameTime {
public:
	// 获取单例实例
	static GameTime* getInstance();

	// 设置时间流速
	void setTimeSpeed(double speed);

	// update时间
	void updateTime();
	void jumpToNextMorning();

	// 以字符串形式获取时间信息
	std::string toString() const;

private:
	// 禁止拷贝和赋值操作
	GameTime(const GameTime&) = delete;
	GameTime& operator=(const GameTime&) = delete;

	// 构造函数
	GameTime(int y = 2024, int m = 1, int d = 1, int h = 0, int min = 0, double speed = 1.0);

	// 规范化时间和日期
	void normalize();

	// 静态实例指针
	static GameTime* instance;

	// 年月日
	int year, month, day;
	int hour, minute;

	// 时间流动速度
	double timeSpeed;

};

#endif // _GAME_TIME_H_
