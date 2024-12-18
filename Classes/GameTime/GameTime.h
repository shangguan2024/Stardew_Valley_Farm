/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTime.h
 * File Function: GameTime��Ķ���
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
	// ��ȡ����ʵ��
	static GameTime* getInstance();

	// ����ʱ������
	void setTimeSpeed(double speed);

	// updateʱ��
	void updateTime();
	void jumpToNextMorning();

	// ���ַ�����ʽ��ȡʱ����Ϣ
	std::string toString() const;

private:
	// ��ֹ�����͸�ֵ����
	GameTime(const GameTime&) = delete;
	GameTime& operator=(const GameTime&) = delete;

	// ���캯��
	GameTime(int y = 2024, int m = 1, int d = 1, int h = 0, int min = 0, double speed = 1.0);

	// �淶��ʱ�������
	void normalize();

	// ��̬ʵ��ָ��
	static GameTime* instance;

	// ������
	int year, month, day;
	int hour, minute;

	// ʱ�������ٶ�
	double timeSpeed;

};

#endif // _GAME_TIME_H_
