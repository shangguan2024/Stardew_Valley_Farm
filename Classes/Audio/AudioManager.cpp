#include "AudioManager.h"

USING_NS_CC;

 // 音频引擎设置
// int g_backgroundMusicSign = DEFAULT_MUSIC_SIGN;
// int g_soundEffectSign = DEFAULT_MUSIC_SIGN;
// float g_backgroundMusicVolumn = DEFAULT_MUSIC_VOLUMN;
// float g_soundEffectVolumn = DEFAULT_MUSIC_VOLUMN;

// // 音频引擎方法
// void audioPlayer(const std::string& audioPath, bool isLoop)
// {
//    if (isLoop) {
//        if (g_backgroundMusicSign != DEFAULT_MUSIC_SIGN) {
//            cocos2d::experimental::AudioEngine::stop(g_backgroundMusicSign);
//        }
//        g_backgroundMusicSign = cocos2d::experimental::AudioEngine::play2d(audioPath, isLoop);
//        cocos2d::experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);
//    }
//    else {
//        g_soundEffectSign = cocos2d::experimental::AudioEngine::play2d(audioPath, isLoop);
//        cocos2d::experimental::AudioEngine::setVolume(g_soundEffectSign, g_soundEffectVolumn);
//    }
// }
