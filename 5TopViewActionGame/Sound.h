#pragma once

#include <SDKwavefile.h>
#include <SDKsound.h>
#include "Singleton.h"

class SoundManager : public Singleton<SoundManager>
{
public:
	CSoundManager* manager;
	std::map<std::string, CSound*> soundmap;

	void Init();

	void PreLoad();
	void Play();
	void Stop();
};

