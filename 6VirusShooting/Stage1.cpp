#include "DXUT.h"
#include "UIPack.h"
#include "Effect.h"
#include "Stage1.h"

void Stage1::Init()
{
	std::cout << "asdf" << std::endl;
	pack = new UIPack;
	pack->Init();
	EffectManager::GetInstance().Create();
}

void Stage1::Update()
{
	std::cout << "iiuiui" << std::endl;
	if(DXUTWasKeyPressed('W'))
		EffectManager::GetInstance().Spawn(MIDDLE, E_AIRSUPPORT);

	pack->Update();
}

void Stage1::Exit()
{
	std::cout << "È£¾Þ" << std::endl;
	pack->Delete();
	EffectManager::GetInstance().Delete();
	delete pack;
}
