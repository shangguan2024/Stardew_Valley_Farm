#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "Constant.h"
#include "SimpleAudioEngine.h"
#include "Audio.h"


class AudioManager
{
public:

    static int   g_backgroundMusicSign;
    static int   g_soundEffectSign;
    static float g_backgroundMusicVolumn;
    static float g_soundEffectVolumn;

    static AudioManager* getInstance();
    bool init();

private:
    void playMusic(const std::string&);
    void playEffect(const std::string&, bool);

private:
    static AudioManager* instance;
    static CocosDenshion::SimpleAudioEngine* audio;
};

#endif
