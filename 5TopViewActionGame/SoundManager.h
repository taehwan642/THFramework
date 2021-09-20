#pragma once
#include <SDKsound.h>
#include <SDKwavefile.h>
#include "Singleton.h"

class SoundManager :
    public Singleton<SoundManager>
{
public:
    std::map <std::wstring, CSound*> soundmap;
    CSoundManager* mng = nullptr;

    // »ý¼ºÀÚ
    SoundManager();

    // Create
    void LoadSound(LPWSTR path, std::wstring tag);
    
    // Play
    void Play(std::wstring tag, long volume = 0, bool isLoop = false);

    // Stop
    void Stop(std::wstring tag);

    // Delete
    void DeleteSounds();
};

