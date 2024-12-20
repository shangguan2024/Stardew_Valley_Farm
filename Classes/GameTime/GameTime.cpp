/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTime.cpp
 * File Function: GameTime类的实现
 * Author:        lyf
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

GameTime::GameTime(int y, int m, int d, int h, int min, int timeStamp, double speed) :
	year(y), month(m), day(d), hour(h), minute(min), timeStamp(timeStamp), timeSpeed(speed)
{
	normalize();
}

// 更新时间
void GameTime::normalize()
{
	// 闰年判断函数
	auto isLeapYear = [](int year) {
		return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		};

	// 如果分钟数大于或等于 60，调整小时数
	if (minute >= 60) {
		hour += minute / 60;
		minute = minute % 60;
	}

	// 如果小时数大于或等于 24，调整天数
	if (hour >= 24) {
		day += hour / 24;
		hour = hour % 24;
	}

	// 判断每个月的天数，并根据日期调整月份和年份
	while (true) {
		int daysInCurrentMonth;

		// 根据月份计算当前月份的天数
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			daysInCurrentMonth = 31;
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11) {
			daysInCurrentMonth = 30;
		}
		else if (month == 2) {
			daysInCurrentMonth = isLeapYear(year) ? 29 : 28;  // 2月处理闰年
		}

		// 如果天数超过当前月的最大天数，调整为下一个月
		if (day > daysInCurrentMonth) {
			day -= daysInCurrentMonth;
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}
		else {
			break; // 如果天数合适，退出循环
		}
	}
}

void GameTime::setTimeSpeed(double speed)
{
	timeSpeed = speed;
}

void GameTime::updateTime()
{
	++timeStamp;
	int gameMinutes = static_cast<int>(timeSpeed);
	minute += gameMinutes;
	normalize();
}

void GameTime::jumpToNextMorning()
{
	timeStamp += (30 - hour) * 60 + minute;
	day += 1;
	hour = 6;
	minute = 0;
	normalize();
}

int GameTime::getTimeStamp()
{
	return timeStamp;
}

std::string GameTime::toString() const
{
	std::string _time = std::to_string(year);
	_time += "/";
	_time += (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
	_time += "/";
	_time += (day < 10) ? "0" + std::to_string(day) : std::to_string(day);
	_time += "\n\n";
	_time += (hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour);
	_time += ":";
	_time += (minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute);
	return _time;
}
