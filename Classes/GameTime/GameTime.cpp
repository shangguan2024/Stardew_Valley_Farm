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

GameTime::GameTime(int y, int m, int d, int h, int min, int timeStamp, double speed) :
	year(y), month(m), day(d), hour(h), minute(min), timeStamp(timeStamp), timeSpeed(speed)
{
	normalize();
}

// ����ʱ��
void GameTime::normalize()
{
	// �����жϺ���
	auto isLeapYear = [](int year) {
		return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		};

	// ������������ڻ���� 60������Сʱ��
	if (minute >= 60) {
		hour += minute / 60;
		minute = minute % 60;
	}

	// ���Сʱ�����ڻ���� 24����������
	if (hour >= 24) {
		day += hour / 24;
		hour = hour % 24;
	}

	// �ж�ÿ���µ����������������ڵ����·ݺ����
	while (true) {
		int daysInCurrentMonth;

		// �����·ݼ��㵱ǰ�·ݵ�����
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			daysInCurrentMonth = 31;
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11) {
			daysInCurrentMonth = 30;
		}
		else if (month == 2) {
			daysInCurrentMonth = isLeapYear(year) ? 29 : 28;  // 2�´�������
		}

		// �������������ǰ�µ��������������Ϊ��һ����
		if (day > daysInCurrentMonth) {
			day -= daysInCurrentMonth;
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}
		else {
			break; // ����������ʣ��˳�ѭ��
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
