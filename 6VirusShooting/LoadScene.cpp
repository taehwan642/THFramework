#include "DXUT.h"
#include "Texture.h"
#include "AniSprite.h"
#include "LoadScene.h"

void LoadScene::LoadAni(std::wstring tag, int startindex, int frameCount)
{
	for (int i = startindex; i < frameCount; ++i)
	{
		const auto& route = tag + L" (" + std::to_wstring(i + 1) + L").png";
		TextureManager::GetInstance().LoadTexture(route);
	}
}

void LoadScene::LoadStart()
{
	th = std::thread([&]()
		{
			//LoadAni(L"Sprites/effect/AirSupprt/airsupport", 0, 15);
			LoadAni(L"Sprites/player/move/6/move", 0, 15);
	/*		LoadAni(L"Sprites/enemy/type1/move/18/move", 0, 30);
			LoadAni(L"Sprites/enemy/type1/sink/18/sink", 0, 28);
			LoadAni(L"Sprites/effect/explo/explosion", 23, 0);
			LoadAni(L"Sprites/effect/AirSupprt/airsupport", 15, 20);
			LoadAni(L"Sprites/Item/machinegun/machine", 0, 30);
			LoadAni(L"Sprites/Item/missile/missile", 0, 30);
			LoadAni(L"Sprites/Item/Torpedo/torpedo", 0, 30);
			LoadAni(L"Sprites/effect/explo/explosion", 0, 23); */
			std::cout << "스레드1끝" << std::endl;
			return 0;
		});


	th3 = std::thread([&]()
		{
			//LoadAni(L"Sprites/effect/AirSupprt/airsupport", 20, 25);
			LoadAni(L"Sprites/player/move/6/move", 15, 30);
			//LoadAni(L"Sprites/enemy/type2/move/18/move", 0, 30);
			//LoadAni(L"Sprites/bullet/EnemyMissile/missile", 0, 30);
			//LoadAni(L"Sprites/enemy/typeboss1/move/move", 0, 15);
			
			std::cout << "스레드3끝" << std::endl;
			return 0;
		});

	th4 = std::thread([&]() {
		//LoadAni(L"Sprites/effect/AirSupprt/airsupport", 25, 31);
		LoadAni(L"Sprites/bullet/mine/mine", 0, 30);
		LoadAni(L"Sprites/bullet/Garbage/type1/trash", 0, 30);
		LoadAni(L"Sprites/bullet/Garbage/type2/trash", 0, 30);
		LoadAni(L"Sprites/Item/toolbox/toolbox", 0, 30);
		LoadAni(L"Sprites/Item/eventbox/eventbox", 0, 30);
		LoadAni(L"Sprites/bullet/Torpedo/torpedo", 0, 30);
		LoadAni(L"Sprites/bullet/PlayerMissile/missile", 0, 30);
		LoadAni(L"Sprites/enemy/typeboss1/move/move", 15, 30);
		std::cout << "스레드4끝" << std::endl;
		return 0;
		});

	th.detach();
	th3.detach();
	th4.join();
}

void LoadScene::Init()
{
	std::cout << "아시발왜이래 ㅋ" << std::endl;
	ans = new AniSprite;
	ans->CreateAnimation(L"Sprites/enemy/type1/move/18/move", 30, 0.05f);
	ans->PlayAnimation(L"Sprites/enemy/type1/move/18/move");
	ans->position = MIDDLE;
}

void LoadScene::Update()
{
	static float tick = 0.f;
	tick += Time::dt;
	if (tick > 3.f)
	{
		LoadStart();
		tick = -999999.f;
	}
	ans->PlayAnimation(L"Sprites/enemy/type1/move/18/move");
}

void LoadScene::Exit()
{
	std::cout << "나가 ㅋ" << std::endl;
}
