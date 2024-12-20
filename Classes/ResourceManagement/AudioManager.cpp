#include "AudioManager.h"

USING_NS_CC;
using namespace CocosDenshion;

AudioManager*      AudioManager::instance   = nullptr;
SimpleAudioEngine* AudioManager::audio      = nullptr;

int   AudioManager::g_backgroundMusicSign       = DEFAULT_MUSIC_SIGN;
int   AudioManager::g_soundEffectSign           = DEFAULT_MUSIC_SIGN;
float AudioManager::g_backgroundMusicVolumn     = DEFAULT_MUSIC_VOLUMN;
float AudioManager::g_soundEffectVolumn         = DEFAULT_MUSIC_VOLUMN;

AudioManager* AudioManager::getInstance()
{   
    if (instance)
        return instance;

    audio = SimpleAudioEngine::getInstance();
    if (!audio)
        return nullptr;

    AudioManager* ret = new AudioManager;

    if (ret && ret->init())
    {
        return instance = ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool AudioManager::init()
{
    audio->setEffectsVolume(g_soundEffectVolumn);
    audio->setBackgroundMusicVolume(g_backgroundMusicVolumn);

    return true;
}

void AudioManager::playMusic(const std::string& audioPath)
{
    
    audio->playBackgroundMusic(audioPath.c_str(), false);
}

void AudioManager::playEffect(const std::string& audioPath, bool isLoop)
{   
    audio->playEffect(audioPath.c_str(), isLoop, 1.0f, 0.0f, 1.0f);
    
}
