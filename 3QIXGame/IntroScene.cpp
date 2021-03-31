#include "DXUT.h"
#include "Director.h"
#include "Effects.h"
#include "Sound.h"
#include "IntroScene.h"

void IntroScene::Init()
{
	introsprite = new Sprite();
	introsprite->layer = -5;
	introsprite->position = { ScreenW / 2, ScreenH / 2 };
	EffectManager::GetInstance()->CreateEffect();
	Sound::GetInstance()->LoadSound(L"Res/Sound/BGM.wav", L"BGM");
	Sound::GetInstance()->LoadSound(L"Res/Sound/_collision.wav", L"Collision");
	Sound::GetInstance()->LoadSound(L"Res/Sound/Win1.wav", L"Win");
	Sound::GetInstance()->LoadSound(L"Res/Sound/Hit.wav", L"Hit");
}

void IntroScene::Update()
{
	delta += DXUTGetElapsedTime();
	std::cout << delta << std::endl;
	if (delta > 3.5f) // 3.5f는 Animation의 2번째 parameter인 float t 의 값과 일치해야만 한다.
	{
		switch (introsprite->frame)
		{
		case 0:

			break;
		case 1: // intro (2).png
			EffectManager::GetInstance()->SpawnEffect({ 859, 184 }, EFLASH);
			break;
		case 2:
			break;
		default:
			break;
		}
		delta = 0;
	}
	if (introsprite->Animation(L"intro", 0.5f, 3))
	{
		Director::GetInstance()->ChangeScene(MENUSCENE);
		return;
	}
}

void IntroScene::Exit()
{
	delete introsprite;
	EffectManager::GetInstance()->DeleteEffect();
}
