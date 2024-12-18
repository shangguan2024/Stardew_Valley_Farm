/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTime.cpp
 * File Function: GameTime���ʵ��
 * Author:        lyf
 * Update Date:   2024/12/13
 ****************************************************************/

#include "GameTime.h"
#include "cocos2d.h"

 // ��̬ʵ����ʼ��
GameTime* GameTime::instance = nullptr;

// ��ȡ����ʵ��
GameTime* GameTime::getInstance()
{
	if (instance == nullptr) {
		// ʹ�� nothrow �����ڴ�
		instance = new (std::nothrow) GameTime();
		// ��ʼ��ʧ��������ʵ��
		if (!instance) {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

GameTime::GameTime(int y, int m, int d, int h, int min, double speed) :
	year(y), month(m), day(d), hour(h), minute(min), timeSpeed(speed)
{
	normalize();
}

// ? ����ʲô��
void GameTime::normalize()
{
	if (minute >= 60) {
		minute = 0;
		hour++;
		if (hour >= 24) {
			hour = 0;
			day++;
			if (day > 30) {
				day = 1;
				month++;
				if (month > 4) {
					month = 1;
					year++;
				}
			}
		}
	}
	// ���ʱ���д�����¸���
	if (minute > 60 || hour >= 24 || day > 30 || month > 4) {
		GameTime::normalize();
	}
}

void GameTime::setTimeSpeed(double speed)
{
	timeSpeed = speed;
}

void GameTime::updateTime()
{
	int gameMinutes = static_cast<int>(timeSpeed);
	minute += gameMinutes;
	normalize();
}

void GameTime::jumpToNextMorning()
{
	day += 1;
	hour = 6;
	minute = 0;
	normalize();
}

std::string GameTime::toString() const
{
	std::string _time = std::to_string(year);
	_time += "/";
	_time += (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
	_time += "/";
	_time += (day < 10) ? "0" + std::to_string(day) : std::to_string(day);
	_time += " ";
	_time += (hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour);
	_time += ":";
	_time += (minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute);
	return _time;
}
