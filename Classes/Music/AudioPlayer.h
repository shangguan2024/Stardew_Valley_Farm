/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     AudioPlayer.h
 * File Function: 音频引擎方法的定义
 * Author:        张翔
 * Update Date:   2024/12/8
 ****************************************************************/

#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_
#include "audio/include/AudioEngine.h"

 // 音频引擎设置
extern int g_backgroundMusicSign;
extern int g_soundEffectSign;
extern float g_backgroundMusicVolumn;
extern float g_soundEffectVolumn;

// 音频引擎方法
void audioPlayer(const std::string& audioPath, bool isLoop);

#endif // !_AUDIO_PLAYER_H_
