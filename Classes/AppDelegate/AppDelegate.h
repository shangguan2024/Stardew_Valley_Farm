/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     AppDelegate.h
 * File Function: AppDelegate��Ķ���
 * Author:        ����
 * Update Date:   2024/12/3
 * License:       MIT License
 ****************************************************************/

#ifndef _APP_DELEGATE_H_
#define _APP_DELEGATE_H_

#include "cocos2d.h"

 /*
  * Class Name:     AppDelegate
  * Class Function: Cocos2d-x Ӧ�ó�����
  */
class AppDelegate : private cocos2d::Application {
public:
	AppDelegate();
	// ��������
	virtual ~AppDelegate();

	// ��ʼ�� OpenGL ����������
	virtual void initGLContextAttrs();

	// ��Ӧ�ó������������׼��������ѭ��ʱ���ô˺���
	virtual bool applicationDidFinishLaunching();

	// ��Ӧ�ó�������̨ʱ���ô˺���
	virtual void applicationDidEnterBackground();

	// ��Ӧ�ó���Ӻ�̨���ص�ǰ̨ʱ���ô˺���
	virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_
