#include "DXUT.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	mng = new CSoundManager();
	// Direct Sound Set Coop Level_ �켱��(Priority)
	mng->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);

	// ���׷��� 2
	mng->SetPrimaryBufferFormat(2, 22050, 16);
}

void SoundManager::LoadSound(LPWSTR path, std::wstring tag)
{
	CSound* snd = nullptr;
	auto iter = soundmap.find(tag); // �ߺ� ó��
	if (iter != soundmap.end())
		return;
	
	if (FAILED(mng->Create(&snd, path, DSBCAPS_CTRLVOLUME, GUID_NULL, 15)))
	{
		std::wcout << "���� ���� " << tag << std::endl;

		if(snd != nullptr)
			delete snd;
	}
	else
	{
		std::wcout << "���� ���� " << tag << std::endl;
		soundmap.emplace(tag, snd);
	}
}

void SoundManager::Play(std::wstring tag,  long volume, bool isLoop)
{
	auto iter = soundmap.find(tag);
	if (iter == soundmap.end())
		return;
	soundmap[tag]->Play(0, isLoop, volume);
}

void SoundManager::Stop(std::wstring tag)
{
	auto iter = soundmap.find(tag);
	if (iter == soundmap.end())
		return;
	soundmap[tag]->Stop();
}

void SoundManager::DeleteSounds()
{
	for (auto iter : soundmap)
	{
		delete iter.second;
	}
	soundmap.clear();
}
