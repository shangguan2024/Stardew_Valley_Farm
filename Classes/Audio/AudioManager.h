#ifndef __AUDIOMANAGER_H__
#define __AUDIOMANAGER_H__

#include "cocos2d.h"

 // ��Ƶ��������
extern int g_backgroundMusicSign;
extern int g_soundEffectSign;
extern float g_backgroundMusicVolumn;
extern float g_soundEffectVolumn;

// ��Ƶ���淽��
void audioPlayer(const std::string& audioPath, bool isLoop);

#endif
