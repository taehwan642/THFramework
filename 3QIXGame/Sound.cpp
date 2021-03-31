#include "DXUT.h"
#include "Sound.h"

Sound::Sound()
{
	mng = new CSoundManager();
	mng->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
	mng->SetPrimaryBufferFormat(22050, 1, 15);
}

void Sound::LoadSound(LPWSTR path, wstring name)
{
	CSound* sound;
	auto iter = soundgroup.find(name);
	if (iter == soundgroup.end()) // 사운드 그룹 안에 내가 찾는 사운드가 중복이 되지 않는다면
	{
		if (FAILED(mng->Create(&sound, path, DSBCAPS_CTRLVOLUME, GUID_NULL, 15)))
		{
			wcout << "S LOAD FAILED : " << name << endl;
		}
		else
		{
			wcout << "S LOAD COMPLETE : " << name << endl;
			soundgroup.emplace(name, sound);
		}
	}
}

void Sound::PlaySFX(wstring name, bool isloop, LONG volume)
{
	auto iter = soundgroup.find(name);
	if (iter == soundgroup.end()) // 안에 찾는 사운드가 없다면
	{
		wcout << "play fail : " << name << endl;
		return;
	}
	iter->second->Reset();
	iter->second->Play(0, isloop, volume);
}

void Sound::StopSFX(wstring name)
{
	auto iter = soundgroup.find(name);
	if (iter == soundgroup.end())
		return;
	iter->second->Stop();
}

void Sound::ReleaseSounds()
{
	delete mng;
	soundgroup.clear();
}
