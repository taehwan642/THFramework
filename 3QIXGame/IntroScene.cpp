#include "DXUT.h"
#include "Director.h"
#include "IntroScene.h"

void IntroScene::Init()
{
}

void IntroScene::Update()
{
	delta += DXUTGetElapsedTime();
	std::cout << delta << std::endl;
	if (delta >= 0.3) // Animation(L"Intro", 1.f, 10) == true
	{
		Director::GetInstance()->ChangeScene(MENUSCENE);
		return;
	}
}

void IntroScene::Exit()
{
}
